#ifndef VIDEOPROCESSOR_H
#define VIDEOPROCESSOR_H

#include <string>

struct VideoInfo
{
    std::string format;
    int width;
    int height;
    double duration;
};

class VideoProcessor
{
public:

    VideoInfo getVideoInfo(
        const std::string& filePath
    );

    bool extractFrame(
        const std::string& input,
        const std::string& output,
        int second
    );

    bool resizeVideo(
        const std::string& input,
        const std::string& output,
        int width,
        int height
    );

    bool convertFormat(
        const std::string& input,
        const std::string& output
    );
};

#endif
