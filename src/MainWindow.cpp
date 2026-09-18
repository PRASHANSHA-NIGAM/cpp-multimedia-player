#include "MainWindow.h"
#include "VideoProcessor.h"

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QVideoWidget>

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QFileDialog>
#include <QFileInfo>
#include <QLabel>
#include <QLineEdit>
#include <QIntValidator>
#include <QDir>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Create multimedia objects
    mediaPlayer = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    videoWidget = new QVideoWidget(this);

    // Connect audio and video
    mediaPlayer->setAudioOutput(audioOutput);
    mediaPlayer->setVideoOutput(videoWidget);

    // Default volume = 70%
    audioOutput->setVolume(0.7);

    // Create GUI
    setupUI();

    // Open button
    connect(
        openButton,
        &QPushButton::clicked,
        this,
        &MainWindow::openVideo
    );

    // Play button
    connect(
        playButton,
        &QPushButton::clicked,
        this,
        &MainWindow::playVideo
    );

    // Pause button
    connect(
        pauseButton,
        &QPushButton::clicked,
        this,
        &MainWindow::pauseVideo
    );

    // Stop button
    connect(
        stopButton,
        &QPushButton::clicked,
        this,
        &MainWindow::stopVideo
    );

    // Extract frame button
    connect(
        extractFrameButton,
        &QPushButton::clicked,
        this,
        &MainWindow::extractFrame
    );

    // Resize button
    connect(
        resizeButton,
        &QPushButton::clicked,
        this,
        &MainWindow::resizeVideo
    );

    // Convert button
    connect(
        convertButton,
        &QPushButton::clicked,
        this,
        &MainWindow::convertVideo
    );

    // Seek slider → media player
    connect(
        seekSlider,
        &QSlider::sliderMoved,
        mediaPlayer,
        &QMediaPlayer::setPosition
    );

    // Media player → seek slider
    connect(
        mediaPlayer,
        &QMediaPlayer::positionChanged,
        seekSlider,
        &QSlider::setValue
    );

    // Set seek slider range according to video duration
    connect(
        mediaPlayer,
        &QMediaPlayer::durationChanged,
        [this](qint64 duration)
        {
            seekSlider->setRange(0, duration);
        }
    );

    // Volume slider
    connect(
        volumeSlider,
        &QSlider::valueChanged,
        [this](int value)
        {
            audioOutput->setVolume(value / 100.0);
        }
    );
}


MainWindow::~MainWindow()
{
}


void MainWindow::setupUI()
{
    setWindowTitle("C++ Multimedia Player");

    resize(900, 650);

    // Central widget
    QWidget *centralWidget = new QWidget(this);

    setCentralWidget(centralWidget);

    // Main layout
    QVBoxLayout *mainLayout =
        new QVBoxLayout(centralWidget);


    // ==========================================
    // VIDEO AREA
    // ==========================================

    mainLayout->addWidget(videoWidget);


    // ==========================================
    // PLAYBACK BUTTONS
    // ==========================================

    QHBoxLayout *buttonLayout =
        new QHBoxLayout();

    openButton =
        new QPushButton("Open Video");

    playButton =
        new QPushButton("Play");

    pauseButton =
        new QPushButton("Pause");

    stopButton =
        new QPushButton("Stop");


    buttonLayout->addWidget(openButton);
    buttonLayout->addWidget(playButton);
    buttonLayout->addWidget(pauseButton);
    buttonLayout->addWidget(stopButton);


    mainLayout->addLayout(buttonLayout);


    // ==========================================
    // SEEK SLIDER
    // ==========================================

    seekSlider =
        new QSlider(Qt::Horizontal);

    seekSlider->setRange(0, 0);

    mainLayout->addWidget(seekSlider);


    // ==========================================
    // VOLUME
    // ==========================================

    QHBoxLayout *volumeLayout =
        new QHBoxLayout();

    QLabel *volumeLabel =
        new QLabel("Volume:");

    volumeSlider =
        new QSlider(Qt::Horizontal);

    volumeSlider->setRange(0, 100);

    volumeSlider->setValue(70);


    volumeLayout->addWidget(volumeLabel);
    volumeLayout->addWidget(volumeSlider);


    mainLayout->addLayout(volumeLayout);


    // ==========================================
    // VIDEO INFORMATION
    // ==========================================

    infoLabel =
        new QLabel("No video selected");

    infoLabel->setWordWrap(true);


    mainLayout->addWidget(infoLabel);


    // ==========================================
    // FRAME EXTRACTION
    // ==========================================

    QHBoxLayout *frameLayout =
        new QHBoxLayout();


    QLabel *frameTimeLabel =
        new QLabel("Frame at second:");


    frameTimeInput =
        new QLineEdit();

    frameTimeInput->setPlaceholderText(
        "Example: 10"
    );

    frameTimeInput->setText("10");


    // Allow only numbers
    frameTimeInput->setValidator(
        new QIntValidator(
            0,
            999999,
            this
        )
    );


    extractFrameButton =
        new QPushButton(
            "Extract Frame"
        );


    frameLayout->addWidget(
        frameTimeLabel
    );

    frameLayout->addWidget(
        frameTimeInput
    );

    frameLayout->addWidget(
        extractFrameButton
    );


    mainLayout->addLayout(frameLayout);


    // ==========================================
    // RESIZE VIDEO
    // ==========================================

    resizeButton =
        new QPushButton(
            "Resize to 720p"
        );


    mainLayout->addWidget(
        resizeButton
    );


    // ==========================================
    // FORMAT CONVERSION
    // ==========================================

    convertButton =
        new QPushButton(
            "Convert MP4 to MKV"
        );


    mainLayout->addWidget(
        convertButton
    );
}


// ==============================================
// OPEN VIDEO
// ==============================================

void MainWindow::openVideo()
{
    QString fileName =
        QFileDialog::getOpenFileName(
            this,
            "Open Video",
            "",
            "Video Files (*.mp4 *.mkv *.avi *.mov);;All Files (*)"
        );


    if (!fileName.isEmpty())
    {
        // Store current video path
        currentVideoPath = fileName;


        // Load video
        mediaPlayer->setSource(
            QUrl::fromLocalFile(
                fileName
            )
        );


        // Start playback
        mediaPlayer->play();


        // Create VideoProcessor
        VideoProcessor processor;


        // Get video information
        VideoInfo info =
            processor.getVideoInfo(
                fileName.toStdString()
            );


        // Display information
        QString information =
            QString(
                "File: %1\n"
                "Format: %2\n"
                "Resolution: %3 x %4\n"
                "Duration: %5 seconds"
            )
            .arg(
                QFileInfo(fileName).fileName()
            )
            .arg(
                QString::fromStdString(
                    info.format
                )
            )
            .arg(
                info.width
            )
            .arg(
                info.height
            )
            .arg(
                info.duration,
                0,
                'f',
                2
            );


        infoLabel->setText(
            information
        );
    }
}


// ==============================================
// PLAY
// ==============================================

void MainWindow::playVideo()
{
    mediaPlayer->play();
}


// ==============================================
// PAUSE
// ==============================================

void MainWindow::pauseVideo()
{
    mediaPlayer->pause();
}


// ==============================================
// STOP
// ==============================================

void MainWindow::stopVideo()
{
    mediaPlayer->stop();
}


// ==============================================
// EXTRACT FRAME
// ==============================================

void MainWindow::extractFrame()
{
    // Check whether video is selected
    if (currentVideoPath.isEmpty())
    {
        infoLabel->setText(
            "Please open a video first."
        );

        return;
    }


    // Read second from input
    bool ok = false;

    int second =
        frameTimeInput
            ->text()
            .toInt(&ok);


    // Validate input
    if (!ok || second < 0)
    {
        infoLabel->setText(
            "Please enter a valid second."
        );

        return;
    }


    // Create output directory
    QDir().mkpath(
        "assets/frames"
    );


    // Output file
    QString outputPath =
        QString(
            "assets/frames/frame_%1.jpg"
        )
        .arg(second);


    // Create processor
    VideoProcessor processor;


    // Extract frame
    bool success =
        processor.extractFrame(
            currentVideoPath.toStdString(),
            outputPath.toStdString(),
            second
        );


    if (success)
    {
        infoLabel->setText(
            QString(
                "Frame extracted successfully!\n"
                "Saved at: %1"
            )
            .arg(outputPath)
        );
    }
    else
    {
        infoLabel->setText(
            "Failed to extract frame."
        );
    }
}


// ==============================================
// RESIZE VIDEO
// ==============================================

void MainWindow::resizeVideo()
{
    // Check whether video is selected
    if (currentVideoPath.isEmpty())
    {
        infoLabel->setText(
            "Please open a video first."
        );

        return;
    }


    // Create output directory
    QDir().mkpath(
        "assets/output"
    );


    // Output path
    QString outputPath =
        "assets/output/yoyo_720p.mp4";


    // Create processor
    VideoProcessor processor;


    // Resize to 1280 x 720
    bool success =
        processor.resizeVideo(
            currentVideoPath.toStdString(),
            outputPath.toStdString(),
            1280,
            720
        );


    if (success)
    {
        infoLabel->setText(
            QString(
                "Video resized successfully!\n"
                "Resolution: 1280 x 720\n"
                "Saved at: %1"
            )
            .arg(outputPath)
        );
    }
    else
    {
        infoLabel->setText(
            "Failed to resize video."
        );
    }
}


// ==============================================
// CONVERT MP4 TO MKV
// ==============================================

void MainWindow::convertVideo()
{
    // Check whether video is selected
    if (currentVideoPath.isEmpty())
    {
        infoLabel->setText(
            "Please open a video first."
        );

        return;
    }


    // Create output directory
    QDir().mkpath(
        "assets/output"
    );


    // Output path
    QString outputPath =
        "assets/output/yoyo_converted.mkv";


    // Create processor
    VideoProcessor processor;


    // Convert format
    bool success =
        processor.convertFormat(
            currentVideoPath.toStdString(),
            outputPath.toStdString()
        );


    if (success)
    {
        infoLabel->setText(
            QString(
                "Video converted successfully!\n"
                "Format: MKV\n"
                "Saved at: %1"
            )
            .arg(outputPath)
        );
    }
    else
    {
        infoLabel->setText(
            "Failed to convert video."
        );
    }
}
