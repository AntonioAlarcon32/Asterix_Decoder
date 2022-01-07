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
#include <hdr/asterix_lib/sensor.h>
#include "hdr/gui/packetdetaildialog.h"
#include <hdr/widgets/custommap.h>
#include "emitterdetailswindow.h"

#include <hdr/gui/preferenceswindow.h>
#include <selectsavedialog.h>
#include <emitfiledialog.h>

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
    void RefreshMap();
    void SaveKMLFile();



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
    void on_ResetPacketsClicked();
    void on_ExportAsKMLCLicked();
    void on_ExportAsCSVCLicked();
    void on_showMarkersCheck_stateChanged(int arg1);
    void on_SeeEmittersDetailsClicked();
    void on_x1Clicked();
    void on_x2Clicked();
    void on_x8Clicked();
    void on_x16Clicked();
    void on_StartMulticastClicked();
};


#endif // FILEWINDOW_H
