#ifndef LIVECAPTUREWINDOW_H
#define LIVECAPTUREWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QHostAddress>
#include <QNetworkDatagram>
#include <hdr/appconfig.h>

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

private slots:
    void ProcessPendingDatagrams();
};

#endif // LIVECAPTUREWINDOW_H
