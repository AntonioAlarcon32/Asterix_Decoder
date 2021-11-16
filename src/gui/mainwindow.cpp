#include "hdr/gui/mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      prefWindow_(nullptr)
{
    ui->setupUi(this);
    appConfig_ = nullptr;
    this->InitialConfig();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete prefWindow_;
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
    QString filePath = QFileDialog::getOpenFileName(this,tr("Open Asterix File"));
    FileWindow *fileWindow = new FileWindow(this, filePath);
    fileWindow->show();
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

