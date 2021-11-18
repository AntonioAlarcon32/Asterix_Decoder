#ifndef FILEWINDOW_H
#define FILEWINDOW_H

#include <QMainWindow>
#include "QFileDialog"
#include "QXmlStreamReader"
#include "QDebug"
#include "QDir"
#include "QMessageBox"
#include "QThread"

#include <../AsterixDecoder/hdr/asterix_lib/asterixfile.h>
#include <appconfig.h>
#include <sensor.h>

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
    void closeEvent(QCloseEvent *event);

signals:
    void startLoading(QString path);
    void packetLoaded();

private slots:
    void on_PacketLoaded();
    void on_FinishLoading();
};


#endif // FILEWINDOW_H
