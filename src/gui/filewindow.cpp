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
    ConnectSignalsSlots();
    ui->widget->SetPosition(WGS84Coordinates(41.29742220817759, 2.083346335275707,0));
    ui->widget->SetZoom(10);
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
}

void FileWindow::on_TimerTick() {
    this->ui->timerLabel->setText(currentTime_.toString("hh:mm:ss"));


    if (secsValue_ != 1000) {
        secsValue_ += 500;
    }

    else {
        this->ui->widget->Clear();
        secsValue_ = 0;
        alreadyAdded_.clear();
    }

    while (packetCounter_ < astFile_->dataBlocks->length()) {
        int timeDiff = currentTime_.msecsTo(astFile_->dataBlocks->at(packetCounter_)->GetTimeOfReception());
        QString ident = astFile_->dataBlocks->at(packetCounter_)->GetIdentifier();

        if (timeDiff >= 0 && timeDiff <= 500) {
            if (alreadyAdded_.indexOf(ident) == -1) {
                DataBlock* dataBlock = astFile_->dataBlocks->at(packetCounter_);
                this->ui->widget->AddCircleMarker(dataBlock->GetPosition(),10, "red");
                packetCounter_++;
                alreadyAdded_.append(ident);
            }
            else if (alreadyAdded_.indexOf(ident) != -1) {
                //DELETE OLD MARKER ADD NEW MARKER
                packetCounter_++;
            }
        }

        else {
            break;
        }
    }
    currentTime_ = currentTime_.addMSecs(500);
}


void FileWindow::on_filtersButton_clicked()
{
    FiltersDialog *filtersDialog = new FiltersDialog(this);
    filtersDialog->exec();
    QString callSign = filtersDialog->callSign_;
    QString address = filtersDialog->address_;
    QString trackNumber = filtersDialog->trackNumber_;
    QList<DataBlock*> filteredDatablocks = QList<DataBlock*>();

    if (callSign != "") {
        astFile_->FilterByCallSign(callSign);
    }
}

