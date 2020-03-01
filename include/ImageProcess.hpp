#ifndef IMAGEPROCESS_HPP
#define IMAGEPROCESS_HPP

#include <QThread>
#include <QImage>
#include <QPixmap>
#include <QString>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <leptonica/allheaders.h>
#include <tesseract/baseapi.h>


class ThreadManager;


class ImageProcess : public QThread
{
    Q_OBJECT
public:
    ImageProcess(ThreadManager* tmanager);
    ~ImageProcess() override;

    void run() override;

signals:
    void sendPlateString(QString);
    void getFrame(cv::Mat*);

public slots:
    void stopThread();
private slots:
    void startThread();
    void terminateThread();

private:
    ThreadManager* m_tmanager;
    bool m_keepRunning = true;
    tesseract::TessBaseAPI* m_tessapi = nullptr;
    char* m_outText = nullptr;
    Pix* m_image = nullptr;

    QImage qt_image;
    cv::Mat m_frame;
};

#endif // IMAGEPROCESS_HPP
