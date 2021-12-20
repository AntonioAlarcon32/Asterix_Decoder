#include "hdr/appconfig.h"


AppConfig::AppConfig()
{
}

AppConfig* AppConfig::GetInstance() {

    if(appConfig_==nullptr){
            appConfig_ = new AppConfig();
        }
        return appConfig_;
}

QList<short> AppConfig::GetSystemAreaCodes() {

    QList<short> systemAreaCodes = QList<short>();

    for (Sensor sensor : this->sensorList_) {
        systemAreaCodes.append(sensor.systemAreaCode);
    }
    return systemAreaCodes;
}

QList<short> AppConfig::GetSystemIdCodes() {

    QList<short> systemIdCodes = QList<short>();

    for (Sensor sensor : this->sensorList_) {
        systemIdCodes.append(sensor.systemIdCode);
    }
    return systemIdCodes;
}

void AppConfig::AddSensor(Sensor sensor) {
    this->sensorList_.append(sensor);
}

QList<int> AppConfig::GetUniqueIds() {

    QList<int> sensorList = QList<int>();

    for (Sensor sensor : this->sensorList_) {
        sensorList.append(sensor.uniqueId);
    }
    return sensorList;
}

void AppConfig::DeleteSensor(int uniqueId) {

    int i = 0;
    while (i < this->sensorList_.length()) {
        if (sensorList_.at(i).uniqueId == uniqueId) {
            sensorList_.removeAt(i);
            return;
        }
        i++;
    }
}

Sensor* AppConfig::GetSensorFromSACSIC(short sac, short sic) {

    int i = 0;
    while (i < this->sensorList_.length()) {
        if (sensorList_.at(i).systemAreaCode == sac && sensorList_.at(i).systemIdCode == sic) {
            return &sensorList_[i];
        }
        i++;
    }
    return nullptr;
}

Sensor* AppConfig::GetSensorInfo(int uniqueId) {
    int i = 0;
    while (i < this->sensorList_.length()) {
        if (sensorList_.at(i).uniqueId == uniqueId) {
            return &sensorList_[i];
        }
        i++;
    }
    return nullptr;
}

void AppConfig::SaveXMLFile(QString path) {

    QFile file(path);

    if (file.exists()) {
        file.remove();
    }

    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("AppConfig");
    xmlWriter.writeStartElement("Sensors");

    QList<int> uniqueIds = this->GetUniqueIds();

    for (int id : uniqueIds) {
        Sensor *sensor = this->GetSensorInfo(id);
        xmlWriter.writeStartElement("Sensor");
        xmlWriter.writeTextElement("unique_id",QString::number(sensor->uniqueId));
        xmlWriter.writeTextElement("description",sensor->sensorDescription);
        xmlWriter.writeTextElement("ip",sensor->sensorIp);
        xmlWriter.writeTextElement("latitude",QString::number(sensor->sensorLatitude,'g',8));
        xmlWriter.writeTextElement("longitude",QString::number(sensor->sensorLongitude,'g',8));
        xmlWriter.writeTextElement("category",QString::number(sensor->category));
        xmlWriter.writeTextElement("system_id_code",QString::number(sensor->systemIdCode));
        xmlWriter.writeTextElement("system_area_code",QString::number(sensor->systemAreaCode));
        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
}

void AppConfig::LoadXMLFile(QString path) {

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        return;
    QXmlStreamReader reader(&file);


    if (reader.readNextStartElement()) {
        if (reader.name() == "AppConfig") {
            if (reader.readNextStartElement()) {
                if (reader.name() == "Sensors") {
                    while (reader.readNextStartElement()) {
                        if (reader.name() == "Sensor") {
                            qDebug() << "Start of Sensor";
                            Sensor sensor = Sensor();
                            while (reader.readNextStartElement()) {
                                if (reader.name() == "ip") {
                                    sensor.sensorIp = reader.readElementText();
                                }
                                else if (reader.name() == "description") {
                                    sensor.sensorDescription = reader.readElementText();
                                }
                                else if (reader.name() == "latitude") {
                                    sensor.sensorLatitude = reader.readElementText().toDouble();
                                }
                                else if (reader.name() == "longitude") {
                                    sensor.sensorLongitude = reader.readElementText().toDouble();
                                }
                                else if (reader.name() == "category") {
                                    sensor.category = reader.readElementText().toInt();
                                }
                                else if (reader.name() == "system_area_code") {
                                    sensor.systemAreaCode = reader.readElementText().toInt();
                                }
                                else if (reader.name() == "system_id_code") {
                                    sensor.systemIdCode = reader.readElementText().toInt();
                                }
                                else if (reader.name() == "unique_id") {
                                    sensor.uniqueId = reader.readElementText().toInt();
                                }
                            }
                            if (sensor.uniqueId != 0) {
                                this->AddSensor(sensor);
                            }
                        }
                    }
                }
            }
        }
    }
}

void AppConfig::ClearSensors() {
    this->sensorList_.clear();
}
AppConfig* AppConfig::appConfig_ = nullptr;;
