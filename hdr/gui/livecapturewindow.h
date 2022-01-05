#ifndef LIVECAPTUREWINDOW_H
#define LIVECAPTUREWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QHostAddress>
#include <QFileDialog>
#include <hdr/appconfig.h>
#include "hdr/asterix_lib/asterixfile.h"
#include "hdr/gui/packetdetaildialog.h"

namespace Ui {
class LiveCaptureWindow;
}

class LiveCaptureWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LiveCaptureWindow(QWidget *parent = nullptr);
    ~LiveCaptureWindow();

private:
    Ui::LiveCaptureWindow *ui;
    QList<QUdpSocket*> udpSockets4_;
    QList<QHostAddress> groupAddresses4_;
    QList<int> udpPorts_;
    AppConfig* appConfig_;
    int packetCounter_;
    AsterixFile* astFile_;

private slots:
    void ProcessPendingDatagrams();
    void on_PacketRowClicked();
    void on_StartCaptureClicked();
    void on_StopCaptureClicked();
    void on_SaveFileClicked();
};

#endif // LIVECAPTUREWINDOW_H
