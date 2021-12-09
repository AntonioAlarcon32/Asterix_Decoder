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

#include <hdr/asterix_lib/asterixfile.h>
#include <hdr/appconfig.h>
#include <hdr/gui/filtersdialog.h>
#include <hdr/sensor.h>
#include "hdr/gui/packetdetaildialog.h"

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
    int packetCounter_;
    QList<QString> alreadyAdded_;
    int secsValue_;
    AppConfig *appConfig_;
    QThread *loadingThread;
    QTimer *playTimer_;
    QTime currentTime_;
    void closeEvent(QCloseEvent *event);
    void ConnectSignalsSlots();
    void SetFileDetailsTab();



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
    void on_filtersButton_clicked();
    void on_PacketRowClicked();
    void on_SaveFileClicked();

};


#endif // FILEWINDOW_H
