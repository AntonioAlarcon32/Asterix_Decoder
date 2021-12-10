#include "livecapturewindow.h"
#include "ui_livecapturewindow.h"

LiveCaptureWindow::LiveCaptureWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LiveCaptureWindow)
{
    ui->setupUi(this);

    appConfig_ = AppConfig::GetInstance();

    QList<int> sensorIDs = appConfig_->GetUniqueIds();
    Sensor sensor = appConfig_->GetSensorInfo(sensorIDs.at(0));

    groupAddress4_ = QHostAddress("225.31.214.1");


    udpSocket4_.bind(QHostAddress::AnyIPv4, 4001, QUdpSocket::ShareAddress);
    udpSocket4_.joinMulticastGroup(groupAddress4_);
    connect(&udpSocket4_, &QUdpSocket::readyRead,
                this, &LiveCaptureWindow::ProcessPendingDatagrams);
}

LiveCaptureWindow::~LiveCaptureWindow()
{
    delete ui;
}

void LiveCaptureWindow::ProcessPendingDatagrams() {
    while (udpSocket4_.hasPendingDatagrams()) {
            QNetworkDatagram dgram = udpSocket4_.receiveDatagram();
            int c = 1;
        }
}
