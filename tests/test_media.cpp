#include <gtest/gtest.h>
#include <string>

// ==========================================
// Test 1: Supported video extensions
// ==========================================

bool isSupportedVideo(const std::string& filename)
{
    if (filename.size() < 4)
        return false;

    std::string extension =
        filename.substr(filename.find_last_of("."));

    return extension == ".mp4" ||
           extension == ".mkv" ||
           extension == ".avi" ||
           extension == ".mov";
}


TEST(VideoTest, SupportedExtension)
{
    EXPECT_TRUE(isSupportedVideo("video.mp4"));
    EXPECT_TRUE(isSupportedVideo("movie.mkv"));
    EXPECT_TRUE(isSupportedVideo("sample.avi"));
    EXPECT_TRUE(isSupportedVideo("video.mov"));
}


// ==========================================
// Test 2: Unsupported extension
// ==========================================

TEST(VideoTest, UnsupportedExtension)
{
    EXPECT_FALSE(isSupportedVideo("document.txt"));
    EXPECT_FALSE(isSupportedVideo("image.jpg"));
    EXPECT_FALSE(isSupportedVideo("file.pdf"));
}


// ==========================================
// Test 3: Volume validation
// ==========================================

bool isValidVolume(int volume)
{
    return volume >= 0 && volume <= 100;
}


TEST(VideoTest, ValidVolume)
{
    EXPECT_TRUE(isValidVolume(0));
    EXPECT_TRUE(isValidVolume(50));
    EXPECT_TRUE(isValidVolume(100));
}


TEST(VideoTest, InvalidVolume)
{
    EXPECT_FALSE(isValidVolume(-1));
    EXPECT_FALSE(isValidVolume(101));
}


// ==========================================
// Main
// ==========================================

int main(
    int argc,
    char **argv
)
{
    ::testing::InitGoogleTest(
        &argc,
        argv
    );

    return RUN_ALL_TESTS();
}
