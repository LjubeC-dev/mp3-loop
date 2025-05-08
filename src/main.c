#include "main.h"

int main(int argc, char *argv[]) {

	if ( argc < 2 ){
		printf("Usage: %s filename.mp3\n",TOOL_NAME);
		return 0;
	}

	const char *source_filename = argv[1];

	if (strlen(source_filename)>200){
		printf("File name too large, try to rename to something short!\n");
		return 0;
	}
	
	if ( strcmp(source_filename,"help") == 0 || strcmp(source_filename,"-h") == 0){
		show_help();
		return 0;
	}

    mpg123_handle *mh = NULL;
    lame_global_flags *lame = NULL;
    short *pcm = NULL, *looped_pcm = NULL;
    unsigned char *mp3_buffer = NULL;
    FILE *out_file = NULL;
    int err;

    mpg123_init();
    mh = mpg123_new(NULL, &err);
    if (!mh) {
        fprintf(stderr, "mpg123 error: %s\n", mpg123_plain_strerror(err));
        return 1;
    }

    if (mpg123_open(mh, argv[1]) != MPG123_OK) {
        fprintf(stderr, "Error opening input: %s\n", mpg123_strerror(mh));
        goto cleanup;
    }

    // get audio properties
    long sample_rate;
    int channels, encoding;
    mpg123_getformat(mh, &sample_rate, &channels, &encoding);
    
    // decode entire PCM (adjust for actual length)
    off_t total_frames;
    mpg123_scan(mh); // accurate frame count for VBR
    total_frames = mpg123_length(mh);
    size_t pcm_size = total_frames * channels;
    pcm = (short*)malloc(pcm_size * sizeof(short));
    size_t bytes_read = 0;
    while (1) {
        size_t chunk;
        err = mpg123_read(mh, pcm + bytes_read/sizeof(short), 
            pcm_size * sizeof(short) - bytes_read, &chunk);
        if (err == MPG123_DONE) break;
        if (err != MPG123_OK) {
            fprintf(stderr, "Decode error: %s\n", mpg123_strerror(mh));
            goto cleanup;
        }
        bytes_read += chunk;
    }
    pcm_size = bytes_read / sizeof(short); // actual decoded samples

    //calculate loops and crossfade
    double duration = (double)total_frames / sample_rate;
    int loops_needed = (int)ceil(TARGET_SECONDS / duration);
    int crossfade_samples = (CROSSFADE_MS * sample_rate) / 1000 * channels;
    if (crossfade_samples > pcm_size) crossfade_samples = pcm_size;

    //build looped PCM
    size_t remaining = pcm_size - crossfade_samples;
    size_t looped_size = pcm_size + (loops_needed - 1) * remaining;
    looped_pcm = (short*)malloc(looped_size * sizeof(short));
    memcpy(looped_pcm, pcm, pcm_size * sizeof(short));
    size_t current_pos = pcm_size;
    for (int i = 1; i < loops_needed; i++) {
        short *prev_end = looped_pcm + current_pos - crossfade_samples;
        short *curr_start = pcm;
        for (int j = 0; j < crossfade_samples; j++) {
            float t = (float)j / crossfade_samples;
            prev_end[j] = (short)(prev_end[j] * (1 - t) + curr_start[j] * t);
        }
        memcpy(looped_pcm + current_pos, pcm + crossfade_samples, remaining * sizeof(short));
        current_pos += remaining;
    }

    // LAME encoder
    lame = lame_init();
    lame_set_in_samplerate(lame, sample_rate);
    lame_set_num_channels(lame, channels);
    lame_set_quality(lame, 5);
    lame_init_params(lame);

	
	char output_filename[210] = "1 hour - "; // [200] - reserved for source_file name, [110] - for "1 hour - "
	strcat(output_filename,source_filename);

    out_file = fopen(output_filename, "wb");
    if (!out_file) {
        fprintf(stderr, "Failed to open output file\n");
        goto cleanup;
    }

    // encode in chunks to avoid buffer overflow
    mp3_buffer = (unsigned char*)malloc(MP3_BUFFER_SIZE);
    int num_samples = current_pos / channels;
    int sample_index = 0;
    while (sample_index < num_samples) {
        int chunk_samples = (num_samples - sample_index > PCM_CHUNK) 
            ? PCM_CHUNK : num_samples - sample_index;
        int mp3_bytes = lame_encode_buffer_interleaved(
            lame, looped_pcm + sample_index * channels,
            chunk_samples, mp3_buffer, MP3_BUFFER_SIZE
        );
        if (mp3_bytes < 0) {
            fprintf(stderr, "Encode error: %d\n", mp3_bytes);
            goto cleanup;
        }
        fwrite(mp3_buffer, 1, mp3_bytes, out_file);
        sample_index += chunk_samples;
    }

    // Flush enc
    int mp3_bytes = lame_encode_flush(lame, mp3_buffer, MP3_BUFFER_SIZE);
    if (mp3_bytes > 0) fwrite(mp3_buffer, 1, mp3_bytes, out_file);

    printf("Success! Created 1-hour %s\n",output_filename);

cleanup:
    if (pcm) free(pcm);
    if (looped_pcm) free(looped_pcm);
    if (mp3_buffer) free(mp3_buffer);
    if (lame) lame_close(lame);
    if (out_file) fclose(out_file);
    if (mh) {
        mpg123_close(mh);
        mpg123_delete(mh);
    }
    mpg123_exit();
    return 0;
}

void show_help(){
	printf("\t Available Commands:\n");
	printf("\t%s filename.mp3\n",TOOL_NAME);
	printf("\t%s -h\n", TOOL_NAME);
	printf("\t%s help\n", TOOL_NAME);
}

