#include "livecapturewindow.h"
#include "ui_livecapturewindow.h"

LiveCaptureWindow::LiveCaptureWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LiveCaptureWindow)
{
    ui->setupUi(this);

    appConfig_ = AppConfig::GetInstance();
    astFile_ = new AsterixFile();

    QList<int> sensorIDs = appConfig_->GetUniqueIds();
    Sensor sensor = appConfig_->GetSensorInfo(sensorIDs.at(0));

    groupAddress4_ = QHostAddress("225.31.214.1");


    udpSocket4_.bind(QHostAddress::AnyIPv4, 10000, QUdpSocket::ShareAddress);
    packetCounter_ = 0;
    bool joined = udpSocket4_.joinMulticastGroup(groupAddress4_);
    connect(&udpSocket4_, &QUdpSocket::readyRead,
                this, &LiveCaptureWindow::ProcessPendingDatagrams);
    connect(this->ui->showPacketDetailsButton, &QAbstractButton::clicked, this, &LiveCaptureWindow::on_PacketRowClicked);

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
    while (udpSocket4_.hasPendingDatagrams()) {
            QNetworkDatagram dgram = udpSocket4_.receiveDatagram();
            QByteArray data = dgram.data();
            packetCounter_++;
            astFile_->AddPacketToList(data);
        }
}



