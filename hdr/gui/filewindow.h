#ifndef FILEWINDOW_H
#define FILEWINDOW_H

#include <QMainWindow>
#include "QFileDialog"
#include "QXmlStreamReader"
#include "QDebug"
#include "QDir"
#include "QMessageBox"

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
    explicit FileWindow(QWidget *parent = nullptr, QString filePath = "");
    ~FileWindow();

private:
    Ui::FileWindow *ui;
    AsterixFile *astFile_;
    AppConfig *appConfig_;

    void DecodeFile(QString filePath);
    void closeEvent(QCloseEvent *event);
};

#endif // FILEWINDOW_H
