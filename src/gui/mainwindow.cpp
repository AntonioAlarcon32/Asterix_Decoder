#include "hdr/gui/mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      astFile()
{
    ui->setupUi(this);
    AsterixFile *ast = new AsterixFile();
    astFile = ast;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionOpen_File_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this,tr("Open Asterix File"));
    astFile->readFile(filePath);
    ui->loadedPackets->setText("Loaded " + QString::number(astFile->numberOfPackets) + " packets");
}

