#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <mpg123.h>
#include <lame/lame.h>

// Tool information
#define TOOL_NAME "mp3_loop"
#define TARGET_SECONDS 3600    // 1-hour loop target
#define CROSSFADE_MS 500       // 500ms crossfade
#define PCM_CHUNK 8192         // Chunk size for PCM processing
#define MP3_BUFFER_SIZE 8192   // Buffer size for LAME encoder

// Function prototypes
void show_help(void);

extern const char *source_filename;

#endif // HEADER_H

