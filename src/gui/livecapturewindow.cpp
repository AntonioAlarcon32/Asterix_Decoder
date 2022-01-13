#include "hdr/gui/livecapturewindow.h"
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
    alreadyAdded_ = QList<QString>();
    udpPorts_ = QList<int>();
    receivedFirst_ = false;
    receiverTimer_ = new QTimer();
    ui->widget->SetPosition(WGS84Coordinates(41.29742220817759, 2.083346335275707,0));
    ui->widget->SetZoom(10);

    QList<int> sensorIDs = appConfig_->GetUniqueIds();

    for (int uniqueId : sensorIDs) {
        Sensor *sensor = appConfig_->GetSensorInfo(uniqueId);
        if (sensor->sensorIp != ""){
            QHostAddress newAddress = QHostAddress(sensor->sensorIp);
            QUdpSocket *newSocket = new QUdpSocket();
            udpSockets4_.append(newSocket);
            groupAddresses4_.append(newAddress);
            udpPorts_.append(sensor->port);
        }
    }

    packetCounter_ = 0;
    connect(this->ui->showPacketDetailsButton, &QAbstractButton::clicked, this, &LiveCaptureWindow::on_PacketRowClicked);
    connect(this->ui->startCaptureButton, &QAbstractButton::clicked, this, &LiveCaptureWindow::on_StartCaptureClicked);
    connect(this->ui->stopCaptureButton, &QAbstractButton::clicked, this, &LiveCaptureWindow::on_StopCaptureClicked);
    connect(this->ui->actionSave_File, &QAction::triggered, this, &LiveCaptureWindow::on_SaveFileClicked);
    connect(this, &LiveCaptureWindow::FirstPacketReceived, this, &LiveCaptureWindow::on_FirstPacketdReceived);
    connect(receiverTimer_, &QTimer::timeout, this, &LiveCaptureWindow::on_TimerTick);


    ui->tableView->setModel(astFile_->packetTable_);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->verticalHeader()->setVisible(false);

    ui->widget->SetNumberOfCycles(20);

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
            QByteArray datagram;
            datagram.resize(int(socket->pendingDatagramSize()));
            socket->readDatagram(datagram.data(), datagram.size());
            packetCounter_++;
            astFile_->AddPacketToList(datagram);
            AddPacketToMap(astFile_->dataBlocks->last());
            if (receivedFirst_ == false) {
                receivedFirst_ = true;
                emit FirstPacketReceived();
            }
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

void LiveCaptureWindow::on_StopCaptureClicked() {
    receiverTimer_->stop();
    for (int i = 0; i < groupAddresses4_.length(); i++) {
        QHostAddress address = groupAddresses4_.at(i);
        QUdpSocket *socket = udpSockets4_.at(i);
        socket->leaveMulticastGroup(address);
    }
}

void LiveCaptureWindow::on_SaveFileClicked() {
    QFileDialog dialog(this);

    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(tr("Valid Files (*.ast *.gps)"));
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setAcceptMode(QFileDialog::AcceptSave);

    QStringList fileNames;

    if (dialog.exec())
        fileNames = dialog.selectedFiles();

    if (fileNames.length() == 1) {
        QString filePath = fileNames.at(0);
        this->astFile_->writeFile(filePath,true);
    }

    else {
    }
}

void LiveCaptureWindow::on_FirstPacketdReceived() {
    DataBlock* first = astFile_->dataBlocks->at(0);
    int hour = first->GetTimeOfReception().hour();
    int min = first->GetTimeOfReception().minute();
    int sec = first->GetTimeOfReception().second();

    currentTime_ = QTime(hour,min,sec,0);
    receiverTimer_->setInterval(50);
    receiverTimer_->start();
}

void LiveCaptureWindow::on_TimerTick() {
    currentTime_ = currentTime_.addMSecs(50);
    this->ui->timerLabel->setText(currentTime_.toString("hh:mm:ss:zzz"));
    RefreshMap();
}

void LiveCaptureWindow::RefreshMap() {
    this->ui->widget->ClearItemsWithTwoCycles();
    alreadyAdded_.clear();
}

void LiveCaptureWindow::AddPacketToMap(DataBlock* dataBlock) {
    QString address = "", id = "", callSign = "", trackNumber = "";
    int color;
    double trackAngle = 400;
    if (dataBlock->GetCategory() == 21) {
        color = CustomMap::CAT21;
        address = dataBlock->GetAddress();
        id = address + "ADSB";
        if (dataBlock->GetCallSign() != "N/A") {
            callSign = dataBlock->GetCallSign();
        }
        else {
            callSign = "";
        }
        trackNumber = dataBlock->GetTrackNumber();
        trackAngle = dataBlock->GetTrackAngle();
    }
    else if (dataBlock->GetCategory() == 20) {
        color = CustomMap::CAT20;
        address = dataBlock->GetAddress();
        id = address + "MLAT20";
        if (dataBlock->GetCallSign() != "N/A") {
            callSign = dataBlock->GetCallSign();
        }
        else {
            callSign = "";
        }
        trackNumber = dataBlock->GetTrackNumber();
        trackAngle = dataBlock->GetTrackAngle();
    }
    else if (dataBlock->GetCategory() == 10 && dataBlock->GetTypeOfTransmission() == "CAT 10: PSR") {
        color = CustomMap::CAT10SMR;
        address = "";
        callSign = "";
        id = dataBlock->GetTrackNumber() + "SMR10";
        trackNumber = dataBlock->GetTrackNumber();
        trackAngle = dataBlock->GetTrackAngle();
    }
    else if (dataBlock->GetCategory() == 10 && dataBlock->GetTypeOfTransmission() == "CAT 10: MLAT") {
        color = CustomMap::CAT10MLAT;
        address = dataBlock->GetAddress();
        id = address + "MLAT10";
        if (dataBlock->GetCallSign() != "N/A") {
            callSign = dataBlock->GetCallSign();
        }
        else {
            callSign = "";
        }
        trackNumber = dataBlock->GetTrackNumber();
        trackAngle = dataBlock->GetTrackAngle();
    }
    if (alreadyAdded_.indexOf(id) == -1) {
        this->ui->widget->AddCircleMarker(dataBlock->GetPosition(),10,color,id,callSign,address,trackNumber,trackAngle);
        alreadyAdded_.append(id);
    }
    else {
        this->ui->widget->DeleteMarker(id);
        this->ui->widget->AddCircleMarker(dataBlock->GetPosition(),10,color,id,callSign,address,trackNumber,trackAngle);
    }
}

void LiveCaptureWindow::on_showMarkersCheck_stateChanged(int arg1)
{
    if (this->ui->showMarkersCheck->isChecked()) {
        this->ui->widget->ShowLabels();
    }

    else if (!this->ui->showMarkersCheck->isChecked()) {
        this->ui->widget->HideLabels();
    }
}


