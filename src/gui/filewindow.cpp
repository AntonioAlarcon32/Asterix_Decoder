#include "hdr/gui/filewindow.h"
#include "ui_filewindow.h"

FileWindow::FileWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FileWindow)
{
    ui->setupUi(this);
    ui->setupUi(this);
    astFile_ = new AsterixFile();
    appConfig_ = AppConfig::GetInstance();
    playTimer_ = new QTimer();
    loadingThread = new QThread();
    packetCounter_ = 0;
    alreadyAdded_ = QList<QString>();
    secsValue_ = 0;
    astFile_->moveToThread(loadingThread);
    ui->widget->SetPosition(WGS84Coordinates(41.29742220817759, 2.083346335275707,0));
    ui->widget->SetZoom(10);
    ConnectSignalsSlots();
}

FileWindow::~FileWindow()
{
    delete astFile_;
    delete ui;
    delete loadingThread;
}

void FileWindow::DecodeFile(QString filePath) {
    loadingThread->start();
    emit startLoading(filePath);
}

void FileWindow::closeEvent(QCloseEvent *event) {
    delete this;
}

void FileWindow::on_PacketLoaded() {
    emit packetLoaded();
}

void FileWindow::on_FinishLoading() {

    ui->tableView->setModel(astFile_->packetTable_);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->loadedPackets->setText("Loaded " + QString::number(astFile_->numberOfPackets) + " packets");

    ui->loadedFlights->setModel(astFile_->emitterTable_);
    ui->loadedFlights->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->loadedFlights->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->loadedFlights->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->loadedFlights->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int hour = astFile_->dataBlocks->first()->GetTimeOfReception().hour();
    int min = astFile_->dataBlocks->first()->GetTimeOfReception().minute();
    int sec = astFile_->dataBlocks->first()->GetTimeOfReception().second();

    this->SetFileDetailsTab();

    currentTime_ = QTime(hour,min,sec,0);
    this->ui->timerLabel->setText(currentTime_.toString("hh:mm:ss"));
    this->show();
    this->raise();
    loadingThread->quit();
    emit finishedLoading();
}

int FileWindow::GetFileLength(QString filePath) {
    return this->astFile_->GetTotalPackets(filePath);
}


void FileWindow::on_playButton_clicked()
{
    playTimer_->start(500);
}

void FileWindow::on_stopButton_clicked()
{
    playTimer_->stop();
}

void FileWindow::ConnectSignalsSlots() {
    connect(this, &FileWindow::startLoading, astFile_, &AsterixFile::readFile);
    connect(astFile_, &AsterixFile::packetLoaded, this, &FileWindow::on_PacketLoaded);
    connect(astFile_, &AsterixFile::finishLoading, this, &FileWindow::on_FinishLoading);
    connect(this->ui->playButton, &QAbstractButton::clicked, this, &FileWindow::on_playButton_clicked);
    connect(this->ui->stopButton, &QAbstractButton::clicked, this, &FileWindow::on_stopButton_clicked);
    connect(playTimer_, &QTimer::timeout, this, &FileWindow::on_TimerTick);
    connect(this->ui->filtersButton, &QAbstractButton::clicked, this, &FileWindow::on_filtersButton_clicked);
    connect(this->ui->showPacketDetailsButton, &QAbstractButton::clicked, this, &FileWindow::on_PacketRowClicked);

}

void FileWindow::on_TimerTick() {

    this->ui->timerLabel->setText(currentTime_.toString("hh:mm:ss"));
}


void FileWindow::on_filtersButton_clicked()
{
    FiltersDialog *filtersDialog = new FiltersDialog(this);
    filtersDialog->exec();
    QString callSign = filtersDialog->callSign_;
    QString address = filtersDialog->address_;
    QString trackNumber = filtersDialog->trackNumber_;

    if (callSign != "") {
        astFile_->FilterByCallSign(callSign);
    }
}

void FileWindow::on_PacketRowClicked() {

    QModelIndexList indexes = ui->tableView->selectionModel()->selection().indexes();
    QModelIndex index = indexes.at(0);
    int packet = index.data().toInt();
    QTreeWidgetItem *packetDetails = astFile_->dataBlocks->at(packet-1)->GetPacketInfo();
    PacketDetailDialog* details = new PacketDetailDialog(this,packetDetails);
    details->show();
    details->raise();
}

void FileWindow::SetFileDetailsTab() {
    QLocale locale = QLocale();

    ui->fileLabel->setText("File Name: " + astFile_->fileInfo_.baseName() + "." + astFile_->fileInfo_.completeSuffix());
    ui->directoryLabel->setText("Directory: " + astFile_->fileInfo_.absoluteDir().absolutePath());
    ui->sizeLabel->setText("File Size: " + locale.formattedDataSize(astFile_->fileInfo_.size()));
    ui->hourLabel->setText("Start Hour: " + astFile_->dataBlocks->at(0)->GetTimeOfReception().toString("hh:mm:ss:zzz") +
                           " ;" + "Final Hour: " + astFile_->dataBlocks->last()->GetTimeOfReception().toString("hh:mm:ss:zzz"));
    QList<int> categories = astFile_->categoryStats_.keys();
    QList<int> values = astFile_->categoryStats_.values();
    this->ui->statsTable->setRowCount(2);
    this->ui->statsTable->setColumnCount(categories.count() + 2);
    QTableWidgetItem *labelCat = new QTableWidgetItem("Category");
    QTableWidgetItem *labelCount = new QTableWidgetItem("Number Of Packets");
    this->ui->statsTable->setItem(0, 0, labelCat);
    this->ui->statsTable->setItem(1, 0, labelCount);
    int i;


    for (i = 0; i < categories.count(); i++) {
        QTableWidgetItem *category = new QTableWidgetItem(QString::number(categories.at(i)));
        this->ui->statsTable->setItem(0, i+1, category);
        QTableWidgetItem *count = new QTableWidgetItem(QString::number(values.at(i)));
        this->ui->statsTable->setItem(1, i+1, count);
    }
    QTableWidgetItem *totalLabel = new QTableWidgetItem("Total");
    QTableWidgetItem *totalCount = new QTableWidgetItem(QString::number(astFile_->numberOfPackets));
    this->ui->statsTable->setItem(0,i+1, totalLabel);
    this->ui->statsTable->setItem(1,i+1, totalCount);

    ui->statsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->statsTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->statsTable->setSelectionMode(QAbstractItemView::NoSelection);
    ui->statsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->statsTable->verticalHeader()->setVisible(false);
}
