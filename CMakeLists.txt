cmake_minimum_required(VERSION 3.16)

project(
    CppMultimediaPlayer
    VERSION 1.0
    DESCRIPTION "C++ Qt Multimedia Player"
    LANGUAGES CXX
)


# ==========================================
# C++ CONFIGURATION
# ==========================================

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(
    CMAKE_BUILD_TYPE
    Release
    CACHE STRING
    "Build type"
)


# ==========================================
# QT AUTOMATION
# ==========================================

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


# ==========================================
# FIND QT6
# ==========================================

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
    Multimedia
    MultimediaWidgets
)


# ==========================================
# SOURCE FILES
# ==========================================

set(SOURCES
    src/main.cpp
    src/MainWindow.cpp
    src/VideoProcessor.cpp
)


# ==========================================
# HEADER FILES
# ==========================================

set(HEADERS
    include/MainWindow.h
    include/VideoProcessor.h
)


# ==========================================
# EXECUTABLE
# ==========================================

add_executable(
    MediaPlayer
    ${SOURCES}
    ${HEADERS}
)


# ==========================================
# INCLUDE DIRECTORY
# ==========================================

target_include_directories(
    MediaPlayer
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)


# ==========================================
# QT LIBRARIES
# ==========================================

target_link_libraries(
    MediaPlayer
    PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Multimedia
    Qt6::MultimediaWidgets
)


# ==========================================
# COMPILER WARNINGS
# ==========================================

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")

    target_compile_options(
        MediaPlayer
        PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )

endif()


# ==========================================
# INSTALLATION
# ==========================================

include(GNUInstallDirs)

install(
    TARGETS MediaPlayer
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)


# ==========================================
# ASSETS INSTALLATION
# ==========================================

install(
    DIRECTORY assets/
    DESTINATION
    ${CMAKE_INSTALL_DATADIR}/MediaPlayer/assets
    OPTIONAL
)
# ==========================================
# TESTING
# ==========================================

enable_testing()

find_package(GTest REQUIRED)

add_executable(
    MediaPlayerTests
    tests/test_media.cpp
)

target_link_libraries(
    MediaPlayerTests
    PRIVATE
    GTest::gtest
)

add_test(
    NAME MediaPlayerTests
    COMMAND MediaPlayerTests
)
