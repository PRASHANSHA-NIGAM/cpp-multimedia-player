#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QMediaPlayer;
class QAudioOutput;
class QVideoWidget;
class QPushButton;
class QSlider;
class QLabel;
class QLineEdit;

class MainWindow : public QMainWindow
{
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupUI();

    void openVideo();
    void playVideo();
    void pauseVideo();
    void stopVideo();
    void extractFrame();
    void resizeVideo();
    void convertVideo();

    QMediaPlayer *mediaPlayer;
    QAudioOutput *audioOutput;
    QVideoWidget *videoWidget;

    QPushButton *openButton;
    QPushButton *playButton;
    QPushButton *pauseButton;
    QPushButton *stopButton;

    QSlider *seekSlider;
    QSlider *volumeSlider;

    QLabel *infoLabel;

    QPushButton *extractFrameButton;
    QPushButton *resizeButton;
    QPushButton *convertButton;

    QLineEdit *frameTimeInput;

    QString currentVideoPath;
};

#endif
