#ifndef LIVECAPTUREWINDOW_H
#define LIVECAPTUREWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QHostAddress>
#include <QNetworkDatagram>
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
    QUdpSocket udpSocket4_;
    QHostAddress groupAddress4_;
    AppConfig* appConfig_;
    int packetCounter_;
    AsterixFile* astFile_;

private slots:
    void ProcessPendingDatagrams();
    void on_PacketRowClicked();
};

#endif // LIVECAPTUREWINDOW_H
