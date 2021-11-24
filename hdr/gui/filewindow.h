#ifndef FILEWINDOW_H
#define FILEWINDOW_H

#include <QMainWindow>
#include "QFileDialog"
#include "QXmlStreamReader"
#include "QDebug"
#include "QDir"
#include "QMessageBox"
#include "QThread"
#include "QTimer"
#include "QQmlContext"

#include <../AsterixDecoder/hdr/asterix_lib/asterixfile.h>
#include <hdr/appconfig.h>
#include <hdr/sensor.h>

#include <hdr/gui/preferenceswindow.h>

namespace Ui {
class FileWindow;
}

class FileWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FileWindow(QWidget *parent = nullptr);
    void DecodeFile(QString filePath);
    int GetFileLength(QString filePath);
    ~FileWindow();

private:
    Ui::FileWindow *ui;
    AsterixFile *astFile_;
    AppConfig *appConfig_;
    QThread *loadingThread;
    QTimer *playTimer_;
    QTime currentTime_;
    void closeEvent(QCloseEvent *event);
    void ConnectSignalsSlots();

signals:
    void startLoading(QString path);
    void packetLoaded();
    void finishedLoading();

private slots:
    void on_PacketLoaded();
    void on_FinishLoading();
    void on_stopButton_clicked();
    void on_playButton_clicked();
    void on_TimerTick();
};


#endif // FILEWINDOW_H
