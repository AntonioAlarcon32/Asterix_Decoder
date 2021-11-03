#include "hdr/gui/mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QXmlStreamReader"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      astFile()
{
    ui->setupUi(this);
    AsterixFile *ast = new AsterixFile();
    astFile = ast;
    appConfig_ = nullptr;
    this->InitialConfig();
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
    ui->tableView->setModel(astFile->table);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->loadedPackets->setText("Loaded " + QString::number(astFile->numberOfPackets) + " packets");
}

void MainWindow::InitialConfig() {
    appConfig_ = AppConfig::GetInstance();
    appConfig_->SetInitialConfig();
}

