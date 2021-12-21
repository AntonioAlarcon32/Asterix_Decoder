#include "livecapturewindow.h"
#include "ui_livecapturewindow.h"

LiveCaptureWindow::LiveCaptureWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LiveCaptureWindow)
{
    ui->setupUi(this);

    appConfig_ = AppConfig::GetInstance();
    astFile_ = new AsterixFile();
    udpSockets4_ = QList<QUdpSocket*>();
    groupAddresses4_ = QList<QHostAddress>();
    udpPorts_ = QList<int>();

    QList<int> sensorIDs = appConfig_->GetUniqueIds();

    for (int uniqueId : sensorIDs) {
        Sensor *sensor = appConfig_->GetSensorInfo(uniqueId);
        QHostAddress newAddress = QHostAddress(sensor->sensorIp);
        QUdpSocket *newSocket = new QUdpSocket();
        udpSockets4_.append(newSocket);
        groupAddresses4_.append(newAddress);
        udpPorts_.append(sensor->port);
    }

    packetCounter_ = 0;
    connect(this->ui->showPacketDetailsButton, &QAbstractButton::clicked, this, &LiveCaptureWindow::on_PacketRowClicked);
    connect(this->ui->startCaptureButton, &QAbstractButton::clicked, this, &LiveCaptureWindow::on_StartCaptureClicked);

    ui->tableView->setModel(astFile_->packetTable_);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->verticalHeader()->setVisible(false);

}

LiveCaptureWindow::~LiveCaptureWindow()
{
    delete ui;
    delete astFile_;
}

void LiveCaptureWindow::on_PacketRowClicked() {

    QModelIndexList indexes = ui->tableView->selectionModel()->selection().indexes();
    QModelIndex index = indexes.at(0);
    int packet = index.data().toInt();
    QTreeWidgetItem *packetDetails = astFile_->dataBlocks->at(packet-1)->GetPacketInfo();
    PacketDetailDialog* details = new PacketDetailDialog(this,packetDetails);
    details->show();
    details->raise();
}

void LiveCaptureWindow::ProcessPendingDatagrams() {
    for (QUdpSocket *socket : udpSockets4_) {
        while (socket->hasPendingDatagrams()) {
            QNetworkDatagram dgram = socket->receiveDatagram();
            QByteArray data = dgram.data();
            packetCounter_++;
            astFile_->AddPacketToList(data);
        }
    }
}

void LiveCaptureWindow::on_StartCaptureClicked() {

    for (int i = 0; i < groupAddresses4_.length(); i++) {
        QHostAddress address = groupAddresses4_.at(i);
        QUdpSocket *socket = udpSockets4_.at(i);
        int port = udpPorts_.at(i);
        socket->bind(QHostAddress::AnyIPv4, port, QUdpSocket::ShareAddress);
        bool joined = socket->joinMulticastGroup(address);
        connect(socket, &QUdpSocket::readyRead,
                        this, &LiveCaptureWindow::ProcessPendingDatagrams);
    }
}



