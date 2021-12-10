#include "hdr/gui/mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      prefWindow_(nullptr),
    liveCapture_(nullptr)

{
    ui->setupUi(this);
    appConfig_ = nullptr;
    this->InitialConfig();
    loadingDialog_ = new QProgressDialog("Decoding Asterix File...", nullptr, 0,0);
    loadingDialog_->reset();
    numberOfPackets_ = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete prefWindow_;
    delete loadingDialog_;
}

void MainWindow::InitialConfig() {

    appConfig_ = AppConfig::GetInstance();

    if (QFile::exists(QDir::currentPath() + "/config.xml")) {
        appConfig_->LoadXMLFile(QDir::currentPath() + "/config.xml");
    }

    else {
        QMessageBox msgBox;
        msgBox.setText("There is no sensor configuration, go to preferences to introduce them");
        msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Open);
        msgBox.setDefaultButton(QMessageBox::Open);
        int option = msgBox.exec();

        switch (option) {
        case QMessageBox::Open:
            prefWindow_ = new PreferencesWindow(this);
            prefWindow_->show();
            prefWindow_->raise();
            break;
        }
    }
}

void MainWindow::on_openFileButton_clicked()
{

    QFileDialog dialog(this);

    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(tr("Valid Files (*.ast *.gps)"));
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setAcceptMode(QFileDialog::AcceptOpen);

    QStringList fileNames;

    if (dialog.exec())
        fileNames = dialog.selectedFiles();


    if (fileNames.length() == 1) {
        QString filePath = fileNames.at(0);
        FileWindow *fileWindow = new FileWindow(this);

        int packets = fileWindow->GetFileLength(filePath);

        loadingDialog_->setMinimum(0);
        loadingDialog_->setMaximum(packets);

        connect(fileWindow, &FileWindow::packetLoaded, this, &MainWindow::on_PacketLoaded);
        connect(fileWindow, &FileWindow::finishedLoading, this, &MainWindow::on_FinishedLoading);
        fileWindow->DecodeFile(filePath);
    }

    else {
        loadingDialog_->reset();
    }
}

void MainWindow::on_preferencesButton_clicked()
{
    if (prefWindow_ == nullptr) {
        prefWindow_ = new PreferencesWindow(this);
        prefWindow_->show();
        prefWindow_->raise();
    }
    else {
        prefWindow_->LoadSensorsToTable();
        prefWindow_->show();
        prefWindow_->raise();
    }
}

void MainWindow::on_exitButton_clicked()
{
    QApplication::quit();
}

void MainWindow::on_PacketLoaded() {

    numberOfPackets_+= 1000;
    loadingDialog_->setValue(numberOfPackets_);
}

void MainWindow::on_FinishedLoading() {
    numberOfPackets_ = 0;
    loadingDialog_->reset();
}


void MainWindow::on_liveCaptureButton_clicked()
{
    if (liveCapture_ == nullptr) {
        liveCapture_ = new LiveCaptureWindow(this);
        liveCapture_->show();
        liveCapture_->raise();
    }
    else {
        liveCapture_->show();
        liveCapture_->raise();
    }

}

