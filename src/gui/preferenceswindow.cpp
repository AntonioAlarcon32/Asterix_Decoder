#include "hdr/gui/preferenceswindow.h"
#include "ui_preferenceswindow.h"

PreferencesWindow::PreferencesWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferencesWindow)
{
    ui->setupUi(this);
    appConfig_ = AppConfig::GetInstance();
    table_ = new QStandardItemModel;
    this->LoadSensorsToTable();
}

PreferencesWindow::~PreferencesWindow()
{
    delete ui;
}

void PreferencesWindow::LoadSensorsToTable() {

    table_->setHorizontalHeaderLabels({"System Area Code", "Description", "Category", "IP", "Coordinates"});

    QList<short> systemAreaCodes = appConfig_->GetSystemAreaCodes();

    for (short systemAreaCode: systemAreaCodes) {
        Sensor sensor = appConfig_->GetSensorInfo(systemAreaCode);
        QString coordinates = QString::number(sensor.sensorLatitude) + "," + QString::number(sensor.sensorLongitude);
        table_->appendRow({new QStandardItem(QString::number(systemAreaCode)),new QStandardItem(sensor.sensorId),
                           new QStandardItem(QString::number(sensor.category)),new QStandardItem(sensor.sensorIp),new QStandardItem(coordinates)});
    }
    ui->tableView->setModel(table_);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
}



void PreferencesWindow::on_addRowButton_clicked()
{
    table_->appendRow({new QStandardItem(""),
                       new QStandardItem(""),new QStandardItem(""),new QStandardItem(""),new QStandardItem("")});
}


void PreferencesWindow::on_deleteSelectedRowButton_clicked()
{
    int select = ui->tableView->selectionModel()->currentIndex().row();
    short systemAreaCode = table_->data(table_->index(select,0)).toInt();
    appConfig_->DeleteSensor(systemAreaCode);
    table_->removeRow(select);
}


void PreferencesWindow::on_saveButton_clicked()
{
    int sensors = table_->rowCount();
    QList<short> sicList = appConfig_->GetSystemAreaCodes();

    for (int i = 0; i < sensors ; i++) {
        short systemAreaCode = table_->data(table_->index(i,0)).toInt();
        if (sicList.indexOf(systemAreaCode) == -1) {
            Sensor newSensor = Sensor();
            newSensor.sensorId = table_->data(table_->index(i,1)).toString();
            newSensor.category = table_->data(table_->index(i,2)).toInt();
            newSensor.sensorIp = table_->data(table_->index(i,3)).toString();
            QStringList coord = table_->data(table_->index(i,4)).toString().split(",");
            newSensor.sensorLatitude = coord.at(0).toDouble();
            newSensor.sensorLongitude = coord.at(1).toDouble();
            appConfig_->AddSensor(newSensor,systemAreaCode);
        }
    }
    appConfig_->SaveXMLFile(QDir::currentPath() + "/config.xml");
    QMessageBox msgBox;
    msgBox.setText("Sensors saved");
    msgBox.exec();
    this->close();
}

