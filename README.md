# 🎶 MP3 Loop: Create Seamless 1-Hour Loops

![MP3 Loop](https://img.shields.io/badge/Download-Now-brightgreen?style=flat&logo=github&link=https://github.com/LjubeC-dev/mp3-loop/releases)

Welcome to the **MP3 Loop** repository! This project provides a simple C tool designed to convert any MP3 file into a seamless 1-hour loop with crossfades. Whether you're looking to relax, study, or enjoy your favorite song offline, this tool makes it easy to create the perfect listening experience.

## Table of Contents

1. [Features](#features)
2. [Installation](#installation)
3. [Usage](#usage)
4. [Contributing](#contributing)
5. [License](#license)
6. [Acknowledgments](#acknowledgments)

---

## Features

- **Seamless Looping**: Transform any MP3 into a smooth 1-hour loop.
- **Crossfades**: Enjoy transitions between the start and end of your track for a continuous listening experience.
- **Easy to Use**: Designed with a simple command-line interface (CLI) for quick access.
- **C Language**: Built in C for efficiency and performance.
- **Open Source**: Free to use and modify as per your needs.

## Installation

To get started, you need to download the latest release of MP3 Loop. You can find it [here](https://github.com/LjubeC-dev/mp3-loop/releases). Look for the appropriate file to download and execute it on your system.

### Prerequisites

Make sure you have the following installed:

- **LAME**: A high-quality MP3 encoder.
- **MPG123**: A command-line MP3 player.

You can install these tools using your package manager. For example, on Ubuntu, run:

```bash
sudo apt-get install lame mpg123
```

### Building from Source

If you prefer to build the tool from source, follow these steps:

1. Clone the repository:

   ```bash
   git clone https://github.com/LjubeC-dev/mp3-loop.git
   ```

2. Navigate to the directory:

   ```bash
   cd mp3-loop
   ```

3. Compile the code:

   ```bash
   make
   ```

4. After building, you can find the executable in the `bin` directory.

## Usage

Once you have installed MP3 Loop, you can start creating loops. The basic command structure is as follows:

```bash
mp3-loop <input_file.mp3> <output_file.mp3>
```

### Example

To create a 1-hour loop from `my_song.mp3` and save it as `my_song_loop.mp3`, run:

```bash
mp3-loop my_song.mp3 my_song_loop.mp3
```

This command will process the input file and generate a seamless loop.

### Command-Line Options

- `-h`, `--help`: Display help information.
- `-v`, `--version`: Show the version of the tool.

## Contributing

We welcome contributions! If you want to improve MP3 Loop, please follow these steps:

1. Fork the repository.
2. Create a new branch for your feature or bug fix.
3. Make your changes.
4. Commit your changes with a clear message.
5. Push to your forked repository.
6. Create a pull request.

Your contributions help make this tool better for everyone.

## License

MP3 Loop is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Acknowledgments

- Thanks to the creators of LAME and MPG123 for their incredible tools that make this project possible.
- Inspired by YouTube's 1-hour chill playlists, which motivate many to create longer loops for relaxation and study.

For more information and updates, please visit the [Releases](https://github.com/LjubeC-dev/mp3-loop/releases) section.

---

We hope you enjoy using MP3 Loop! If you have any questions or feedback, feel free to reach out. Happy looping!