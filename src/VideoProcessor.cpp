#include "VideoProcessor.h"

#include <array>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

VideoInfo VideoProcessor::getVideoInfo(const std::string& filePath)
{
    VideoInfo info;

    // Default values
    info.format = "Unknown";
    info.width = 0;
    info.height = 0;
    info.duration = 0;

    // FFprobe command
    std::string command =
        "ffprobe -v error "
        "-select_streams v:0 "
        "-show_entries stream=width,height "
        "-show_entries format=format_name,duration "
        "-of default=noprint_wrappers=1:nokey=1 "
        "\"" + filePath + "\"";

    std::array<char, 256> buffer;
    std::string result;

    // Run FFprobe
    FILE* pipe = popen(command.c_str(), "r");

    if (!pipe)
    {
        std::cerr << "Failed to run ffprobe.\n";
        return info;
    }

    // Read FFprobe output
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr)
    {
        result += buffer.data();
    }

    pclose(pipe);

    // Parse output
    std::istringstream stream(result);

    std::string width;
    std::string height;
    std::string format;
    std::string duration;

    std::getline(stream, width);
    std::getline(stream, height);
    std::getline(stream, format);
    std::getline(stream, duration);

    try
    {
        if (!width.empty())
            info.width = std::stoi(width);

        if (!height.empty())
            info.height = std::stoi(height);

        if (!format.empty())
            info.format = format;

        if (!duration.empty())
            info.duration = std::stod(duration);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error parsing video information: "
                  << e.what() << "\n";
    }

    return info;
}


// Extract one frame from video
bool VideoProcessor::extractFrame(
    const std::string& input,
    const std::string& output,
    int second)
{
    // Prevent negative time
    if (second < 0)
    {
        std::cerr << "Invalid time. Second cannot be negative.\n";
        return false;
    }

    // FFmpeg command
    std::string command =
        "ffmpeg -y "
        "-ss " + std::to_string(second) +
        " -i \"" + input + "\" "
        "-frames:v 1 "
        "\"" + output + "\"";

    std::cout << "Extracting frame at "
              << second
              << " second...\n";

    // Execute FFmpeg
    int result = system(command.c_str());

    if (result == 0)
    {
        std::cout << "Frame extracted successfully: "
                  << output << "\n";

        return true;
    }

    std::cerr << "Failed to extract frame.\n";

    return false;
}
bool VideoProcessor::resizeVideo(
    const std::string& input,
    const std::string& output,
    int width,
    int height)
{
    if (width <= 0 || height <= 0)
    {
        std::cerr << "Invalid video dimensions.\n";
        return false;
    }

    std::string command =
        "ffmpeg -y "
        "-i \"" + input + "\" "
        "-vf scale=" + std::to_string(width) +
        ":" + std::to_string(height) +
        " "
        "-c:a copy "
        "\"" + output + "\"";

    std::cout << "Resizing video to "
              << width << "x" << height
              << "...\n";

    int result = system(command.c_str());

    if (result == 0)
    {
        std::cout << "Video resized successfully: "
                  << output << "\n";

        return true;
    }

    std::cerr << "Failed to resize video.\n";

    return false;
}
bool VideoProcessor::convertFormat(
    const std::string& input,
    const std::string& output)
{
    if (input.empty() || output.empty())
    {
        std::cerr << "Invalid input or output path.\n";
        return false;
    }

    std::string command =
        "ffmpeg -y "
        "-i \"" + input + "\" "
        "\"" + output + "\"";

    std::cout << "Converting video format...\n";

    int result = system(command.c_str());

    if (result == 0)
    {
        std::cout
            << "Video converted successfully: "
            << output
            << "\n";

        return true;
    }

    std::cerr
        << "Failed to convert video.\n";

    return false;
}
