# C++ Multimedia Player

A Linux-based multimedia player built using **C++17, Qt 6, FFmpeg, and CMake**.

The project demonstrates multimedia playback, basic video processing, automated testing, build automation, deployment packaging, and CI/CD using GitHub Actions.

---

## Features

* Video file selection
* Video playback
* Play, Pause, and Stop controls
* Video seeking
* Volume control
* Basic video information
* Frame extraction using FFmpeg
* Video resizing to 720p
* Video format conversion
* Automated unit testing
* CMake-based build system
* Bash build, test, and deployment scripts
* GitHub Actions CI pipeline
* Automated GitHub releases
* Linux deployment package generation

---

## Technologies

| Technology         | Purpose                                    |
| ------------------ | ------------------------------------------ |
| **C++17**          | Core application development               |
| **Qt 6**           | GUI and multimedia functionality           |
| **FFmpeg**         | Video processing and media operations      |
| **CMake**          | Build configuration and project management |
| **GoogleTest**     | Unit testing                               |
| **Bash**           | Build, testing, and deployment automation  |
| **Git**            | Version control                            |
| **GitHub Actions** | CI/CD automation                           |
| **Linux**          | Development and deployment environment     |

---

## Project Structure

```text
cpp-multimedia-player/
│
├── src/
│   ├── main.cpp
│   ├── MainWindow.cpp
│   └── VideoProcessor.cpp
│
├── include/
│   ├── MainWindow.h
│   └── VideoProcessor.h
│
├── tests/
│   └── test_media.cpp
│
├── scripts/
│   ├── build.sh
│   ├── test.sh
│   └── deploy.sh
│
├── assets/
│   ├── frames/
│   └── output/
│
├── .github/
│   └── workflows/
│       ├── ci.yml
│       └── release.yml
│
├── CMakeLists.txt
├── README.md
└── .gitignore
```

---

## Architecture

The application is divided into separate components to keep the GUI, multimedia functionality, and video-processing logic organized.

```text
                    C++ Multimedia Player
                            │
              ┌─────────────┴─────────────┐
              │                           │
        MainWindow                   VideoProcessor
              │                           │
              │                           ├── Frame Extraction
              │                           ├── Video Resize
              │                           └── Format Conversion
              │
              ▼
        Qt Multimedia
              │
              ▼
           FFmpeg
```

### MainWindow

`MainWindow` manages the application's graphical user interface and user interactions.

Responsibilities include:

* Creating and managing the GUI
* Opening video files
* Play, Pause, and Stop controls
* Seek functionality
* Volume control
* Connecting UI actions with multimedia functionality

### VideoProcessor

`VideoProcessor` handles basic video-processing operations using FFmpeg.

Responsibilities include:

* Extracting video frames
* Resizing videos
* Converting video formats
* Executing FFmpeg-based processing operations

---

## Requirements

The project is designed for a Linux environment.

Install the required dependencies:

```bash
sudo apt update

sudo apt install -y \
    build-essential \
    cmake \
    git \
    pkg-config \
    ffmpeg \
    qt6-base-dev \
    qt6-multimedia-dev \
    libgtest-dev
```

---

## Build

Clone the repository:

```bash
git clone https://github.com/PRASHANSHA-NIGAM/cpp-multimedia-player.git
```

Navigate to the project directory:

```bash
cd cpp-multimedia-player
```

Configure the project using CMake:

```bash
cmake -S . -B build
```

Build the application:

```bash
cmake --build build
```

---

## Run

After a successful build, start the application with:

```bash
./build/MediaPlayer
```

The Qt-based GUI will open and allow you to select and play a video file.

---

## Testing

The project uses **GoogleTest** and **CTest** for automated unit testing.

Run the test suite using CTest:

```bash
ctest --test-dir build --output-on-failure
```

You can also use the automated test script:

```bash
./scripts/test.sh
```

Example result:

```text
100% tests passed, 0 tests failed
```

---

## Video Processing

FFmpeg is used for basic video-processing operations.

### Frame Extraction

The application can extract frames from a video and save them as image files.

Example output:

```text
assets/
└── frames/
    ├── yoyo_frame.jpg
    ├── frame_4.jpg
    └── frame_10.jpg
```

### Video Resizing

The project supports resizing a video to 720p.

Example:

```text
Input:
yoyo.mp4

Output:
yoyo_720p.mp4
```

### Format Conversion

The application supports video format conversion using FFmpeg.

Example:

```text
MP4 → MKV
```

---

## Build Automation

The project includes Bash scripts for automating common development tasks.

### Build Script

Run:

```bash
./scripts/build.sh
```

This script configures and builds the application using CMake.

### Test Script

Run:

```bash
./scripts/test.sh
```

This script builds the test target and executes the automated test suite.

### Deployment Script

Run:

```bash
./scripts/deploy.sh
```

This script:

1. Configures a Release build
2. Builds the application
3. Installs the application files
4. Creates the deployment package

---

## Deployment Package

The deployment script generates a Linux package:

```text
packages/MediaPlayer-Linux.tar.gz
```

The package contains the application executable and required project assets:

```text
MediaPlayer-Linux.tar.gz
│
├── bin/
│   └── MediaPlayer
│
└── share/
    └── MediaPlayer/
        └── assets/
```

The generated application executable is a Linux **x86-64 ELF executable**.

---

## CI/CD

GitHub Actions is used to automate the build, testing, and packaging process.

For every push to the `main` branch, the CI pipeline performs:

```text
Git Push
   │
   ▼
Checkout Code
   │
   ▼
Install Dependencies
   │
   ▼
Configure CMake
   │
   ▼
Build Application
   │
   ▼
Run Tests
   │
   ▼
Create Deployment Package
   │
   ▼
Upload Artifact
```

CI workflow:

```text
.github/workflows/ci.yml
```

This helps ensure that changes are automatically built and tested before being considered ready.

---

## Automated Releases

Version tags trigger the automated release workflow.

For example:

```bash
git tag v1.0.0
git push origin v1.0.0
```

The release pipeline performs:

```text
Version Tag
    │
    ▼
Build
    │
    ▼
Run Tests
    │
    ▼
Create Package
    │
    ▼
Create GitHub Release
    │
    ▼
MediaPlayer-Linux.tar.gz
```

Release workflow:

```text
.github/workflows/release.yml
```

---

## Release

Current release:

```text
v1.0.0
```

The release package is generated automatically as:

```text
MediaPlayer-Linux.tar.gz
```

---

## Development Workflow

The project follows a simple development and delivery workflow:

```text
Development
     │
     ▼
Git Commit
     │
     ▼
Git Push
     │
     ▼
GitHub Actions
     │
     ├── Build
     ├── Test
     └── Package
     │
     ▼
Version Tag
     │
     ▼
Automated Release
```

---

## Key Engineering Practices

The project demonstrates the following software engineering practices:

* Modular C++ design
* Header/source file separation
* Object-oriented programming
* CMake-based build management
* Automated unit testing
* Bash scripting and automation
* Version control using Git
* CI/CD using GitHub Actions
* Automated deployment packaging
* Versioned software releases
* Linux-based development

---

## Future Improvements

Possible future enhancements include:

* Playlist support
* Subtitle support
* Playback speed control
* Improved error handling
* Cross-platform builds
* Hardware-accelerated video decoding
* More comprehensive unit and integration tests

---

## License

This project is intended for **educational and portfolio purposes**.

https://github.com/user-attachments/assets/117bc428-8623-464e-a77b-90bd7dc3a6e9

https://github.com/user-attachments/assets/9ba3d216-0741-4105-8cb5-c9703860e04f





