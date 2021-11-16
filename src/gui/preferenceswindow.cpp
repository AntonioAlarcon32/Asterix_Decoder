#include "hdr/gui/preferenceswindow.h"
#include "ui_preferenceswindow.h"

PreferencesWindow::PreferencesWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferencesWindow)
{
    ui->setupUi(this);
    appConfig_ = AppConfig::GetInstance();
    table_ = new QStandardItemModel;
    changesMade_ = false;
    this->LoadSensorsToTable();
}

PreferencesWindow::~PreferencesWindow()
{
    delete ui;
}

void PreferencesWindow::LoadSensorsToTable() {
    table_->clear();
    changesMade_ = false;

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

void PreferencesWindow::SaveSensorsToConfig() {

    int sensors = table_->rowCount();
    appConfig_->ClearSensors();
    for (int i = 0; i < sensors ; i++) {
        short systemAreaCode = table_->data(table_->index(i,0)).toInt();
        Sensor newSensor = Sensor();
        newSensor.sensorId = table_->data(table_->index(i,1)).toString();
        newSensor.category = table_->data(table_->index(i,2)).toInt();
        newSensor.sensorIp = table_->data(table_->index(i,3)).toString();
        QStringList coord = table_->data(table_->index(i,4)).toString().split(",");
        newSensor.sensorLatitude = coord.at(0).toDouble();
        newSensor.sensorLongitude = coord.at(1).toDouble();
        appConfig_->AddSensor(newSensor,systemAreaCode);
    }
    appConfig_->SaveXMLFile(QDir::currentPath() + "/config.xml");

}



void PreferencesWindow::on_addRowButton_clicked()
{
    changesMade_ = true;
    table_->appendRow({new QStandardItem(""),
                       new QStandardItem(""),new QStandardItem(""),new QStandardItem(""),new QStandardItem("")});
}


void PreferencesWindow::on_deleteSelectedRowButton_clicked()
{
    changesMade_ = true;
    int select = ui->tableView->selectionModel()->currentIndex().row();
    table_->removeRow(select);
}


void PreferencesWindow::on_saveButton_clicked()
{
    if (changesMade_) {
        SaveSensorsToConfig();
    }
    QDialog::accept();
}

void PreferencesWindow::on_cancelButton_clicked()
{
    this->reject();
}

void PreferencesWindow::reject() {

    if (changesMade_) {
        QMessageBox msgBox;
        msgBox.setText("You have modified the sensors, Do you want to save changes?");
        msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Save);
        msgBox.setDefaultButton(QMessageBox::Open);
        int option = msgBox.exec();

        switch (option) {
        case QMessageBox::Save:
            SaveSensorsToConfig();
            break;
        }
    }
    QDialog::reject();
}

