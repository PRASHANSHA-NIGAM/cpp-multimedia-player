# C++ Multimedia Player

A Linux-based multimedia player built using C++17, Qt 6, FFmpeg, and CMake.

The project demonstrates multimedia playback, basic video processing, automated testing, build automation, and CI/CD using GitHub Actions.

---

## Features

- Video playback
- Play, Pause, and Stop controls
- Video file selection
- Video seeking
- Volume control
- Video information
- Frame extraction using FFmpeg
- Video resizing to 720p
- Video format conversion
- Automated unit testing
- CMake-based build system
- Bash build, test, and deployment scripts
- GitHub Actions CI pipeline
- Automated GitHub releases
- Linux deployment package generation

---

## Technologies

| Technology | Purpose |
|------------|---------|
| C++17 | Application development |
| Qt 6 | GUI and multimedia functionality |
| FFmpeg | Video processing |
| CMake | Build configuration |
| GoogleTest | Unit testing |
| Bash | Build and deployment automation |
| Git | Version control |
| GitHub Actions | CI/CD |
| Linux | Development and deployment environment |

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
Architecture

The application is divided into separate components.

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
              └── Qt Multimedia
                        │
                        ▼
                      FFmpeg
MainWindow

Responsible for:

Creating the GUI
Opening video files
Play/Pause/Stop controls
Seek functionality
Volume control
Connecting UI actions with multimedia functionality
VideoProcessor

Responsible for basic video-processing operations such as:

Extracting video frames
Resizing videos
Converting video formats
Running FFmpeg processing commands
Requirements

The project is designed for Linux.

Install the required packages:

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
Build

Clone the repository:

git clone https://github.com/PRASHANSHA-NIGAM/cpp-multimedia-player.git

Enter the project directory:

cd cpp-multimedia-player

Configure the project:

cmake -S . -B build

Build the application:

cmake --build build
Run

After a successful build:

./build/MediaPlayer

The Qt GUI will start and allow you to select and play a video file.

Testing

The project uses GoogleTest and CTest for unit testing.

Run:

ctest --test-dir build --output-on-failure

Or use the automated test script:

./scripts/test.sh

Example result:

100% tests passed, 0 tests failed
Video Processing

FFmpeg is used for basic video-processing operations.

Frame Extraction

The application can extract frames from a video and save them as image files.

Example output:

assets/frames/
├── yoyo_frame.jpg
├── frame_4.jpg
└── frame_10.jpg
Video Resizing

The project supports resizing a video to 720p.

Example:

Input:
yoyo.mp4

Output:
yoyo_720p.mp4
Format Conversion

The application can convert video formats using FFmpeg.

Example:

MP4 → MKV
Build Automation

The project includes Bash scripts to automate common development tasks.

Build
./scripts/build.sh

This configures and builds the application using CMake.

Test
./scripts/test.sh

This builds the test target and executes the test suite.

Deployment
./scripts/deploy.sh

This creates a Release build and generates a Linux deployment package.

Deployment Package

The deployment script generates:

packages/MediaPlayer-Linux.tar.gz

The package contains:

MediaPlayer-Linux.tar.gz
│
├── bin/
│   └── MediaPlayer
│
└── share/
    └── MediaPlayer/
        └── assets/

The generated executable is a Linux x86-64 ELF executable.

CI/CD

GitHub Actions is used to automate the build and testing process.

For every push to the main branch, the CI pipeline:

Git Push
   ↓
Checkout Code
   ↓
Install Dependencies
   ↓
Configure CMake
   ↓
Build Application
   ↓
Run Tests
   ↓
Create Deployment Package
   ↓
Upload Artifact

Workflow file:

.github/workflows/ci.yml
Automated Releases

Version tags trigger the release workflow.

Example:

git tag v1.0.0
git push origin v1.0.0

The release pipeline:

Version Tag
    ↓
Build
    ↓
Test
    ↓
Package
    ↓
GitHub Release
    ↓
MediaPlayer-Linux.tar.gz

Release workflow:

.github/workflows/release.yml
Version

Current release:

v1.0.0
Development Workflow

The project follows a basic software development workflow:

Development
     ↓
Git Commit
     ↓
Git Push
     ↓
GitHub Actions
     ↓
Build
     ↓
Unit Tests
     ↓
Package
     ↓
Release
Future Improvements

Possible future enhancements include:

Playlist support
Subtitle support
Playback speed control
Improved error handling
Cross-platform builds
Hardware-accelerated video decoding
More comprehensive unit and integration tests

License

This project is intended for educational and portfolio purposes.

