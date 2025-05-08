
# 🎵 mp3-loop

**mp3-loop** is a lightweight C program that converts any MP3 audio file into a seamless **1-hour loop**. Inspired by those long, relaxing **YouTube playlists** that loop your favorite tracks for hours, this tool gives you the power to do the same — but offline, and with your own audio files.

---

## ✨ Why?

You’ve probably come across those 1-hour versions of songs on YouTube — ambient tracks, game soundtracks, lofi beats, or even meme songs. They help people relax, study, focus, or just enjoy a good vibe.

**So taste this medicine:**

```bash
mp3_loop your-audio.mp3
````

…and enjoy your favorite track on loop, without ads, buffering, or distractions.

---

## 🛠 Requirements

Make sure you have the following dependencies installed:

* **libmpg123** – MP3 decoding
* **libmp3lame** – MP3 encoding
* **libsndfile** – (used via pkg-config)
* **CMake** (v3.12 or higher)
* **GCC** or compatible C compiler

### Install on Ubuntu/Debian:

```bash
sudo apt update
sudo apt install build-essential cmake libmpg123-dev libmp3lame-dev libsndfile1-dev
```

---

## 🧱 Building the Project

1. Clone the repository:

```bash
git clone https://github.com/zephurion/mp3-loop.git
cd mp3-loop
```

2. Configure and build using CMake:

```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```

This will produce an executable called `mp3_loop` inside the `build/` folder.

---

## ▶️ How to Use

Run the tool from the build directory:

```bash
./mp3_loop your-audio.mp3
```

If everything goes well, you'll get a new file:

```
1 hour - your-audio.mp3
```

It’s the same track, seamlessly looped until it hits **exactly 1 hour** with a subtle crossfade between loops.

Need help?

```bash
./mp3_loop help
# or
./mp3_loop -h
```

---

## 📁 Project Structure

```
mp3-loop/
├── CMakeLists.txt         # CMake build file
├── include/
│   └── main.h             # Header for function declarations
├── src/
│   └── main.c             # Main program logic
├── build/                 # Build output (created after compiling)
└── README.md
```

---

## 💡 Tip

Want to loop an audio meme or a soundtrack from a game? Just download it as MP3, and let `mp3_loop` do the rest.

---

## 📃 License

MIT License — feel free to fork, modify, and share.

---

Enjoy looping. 🌀
