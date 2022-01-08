#ifndef LIVECAPTUREWINDOW_H
#define LIVECAPTUREWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QHostAddress>
#include <QFileDialog>
#include <QTimer>
#include <QTime>
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
    QTime currentTime_;
    QTimer *receiverTimer_;
    int packetCounter_;
    int mapCounter_;
    AsterixFile* astFile_;
    bool receivedFirst_;
    QList<QString> alreadyAdded_;
    void RefreshMap();

signals:
    void FirstPacketReceived();

private slots:
    void ProcessPendingDatagrams();
    void on_PacketRowClicked();
    void on_StartCaptureClicked();
    void on_StopCaptureClicked();
    void on_SaveFileClicked();
    void on_FirstPacketdReceived();
    void on_TimerTick();
    void AddPacketToMap(DataBlock* dataBlock);
    void on_showMarkersCheck_stateChanged(int arg1);
};

#endif // LIVECAPTUREWINDOW_H
