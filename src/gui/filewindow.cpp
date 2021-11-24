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
    astFile_->moveToThread(loadingThread);
    ConnectSignalsSlots();

    QQuickWidget *view = ui->quickWidget;
    QQmlContext *context = view->rootContext();
    view->show();
    context->setContextProperty("testWindow", this);
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
    ui->loadedPackets->setText("Loaded " + QString::number(astFile_->numberOfPackets) + " packets");

    ui->loadedFlights->setModel(astFile_->emitterTable_);
    ui->loadedFlights->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->loadedFlights->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->loadedFlights->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->loadedFlights->setEditTriggers(QAbstractItemView::NoEditTriggers);

    currentTime_ = astFile_->dataBlocks->first()->GetTimeOfReception();
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
    playTimer_->start(1000);
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
}

void FileWindow::on_TimerTick() {
    currentTime_ = currentTime_.addSecs(1);
    this->ui->timerLabel->setText(currentTime_.toString("hh:mm:ss"));
}

