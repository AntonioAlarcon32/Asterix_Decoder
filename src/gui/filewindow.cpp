#include "hdr/gui/filewindow.h"
#include "ui_filewindow.h"

FileWindow::FileWindow(QWidget *parent, QString filePath) :
    QMainWindow(parent),
    ui(new Ui::FileWindow)
{
    ui->setupUi(this);
    ui->setupUi(this);
    astFile_ = AsterixFile();;
    appConfig_ = AppConfig::GetInstance();
    this->DecodeFile(filePath);
}

FileWindow::~FileWindow()
{
    delete ui;
}

void FileWindow::DecodeFile(QString filePath) {
    astFile_.readFile(filePath);
    ui->tableView->setModel(astFile_.table);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->loadedPackets->setText("Loaded " + QString::number(astFile_.numberOfPackets) + " packets");
}
