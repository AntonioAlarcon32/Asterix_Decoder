#include "appconfig.h"


AppConfig::AppConfig()
{
    this->value = 0;
}

AppConfig* AppConfig::GetInstance() {

    if(appConfig_==nullptr){
            appConfig_ = new AppConfig();
        }
        return appConfig_;
}

QList<short> AppConfig::GetSystemAreaCodes() {
    return this->dataList.keys();
}

void AppConfig::AddSensor(Sensor sensor, short systemAreaCode) {

    this->dataList.insert(systemAreaCode, sensor);
}

void AppConfig::DeleteSensor(short systemAreaCode) {
    this->dataList.remove(systemAreaCode);
    int c = 1;
}

Sensor AppConfig::GetSensorInfo(short systemAreaCode) {
    return this->dataList.value(systemAreaCode);
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

    QList<short> systemAreaCodes = this->GetSystemAreaCodes();

    for (short sic : systemAreaCodes) {
        Sensor sensor = this->GetSensorInfo(sic);
        xmlWriter.writeStartElement("Sensor");
        xmlWriter.writeTextElement("id",sensor.sensorId);
        xmlWriter.writeTextElement("ip",sensor.sensorIp);
        xmlWriter.writeTextElement("latitude",QString::number(sensor.sensorLatitude,'g',8));
        xmlWriter.writeTextElement("longitude",QString::number(sensor.sensorLongitude,'g',8));
        xmlWriter.writeTextElement("category",QString::number(sensor.category));
        xmlWriter.writeTextElement("system_area_code",QString::number(sic));
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
                            short systemAreaCode = 0;
                            while (reader.readNextStartElement()) {
                                if (reader.name() == "ip") {
                                    sensor.sensorIp = reader.readElementText();
                                }
                                else if (reader.name() == "id") {
                                    sensor.sensorId = reader.readElementText();
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
                                    systemAreaCode = (short) reader.readElementText().toInt();
                                }
                            }
                            if (systemAreaCode != 0) {
                                this->AddSensor(sensor,systemAreaCode);
                            }
                        }
                    }
                }
            }
        }
    }
}

void AppConfig::ClearSensors() {
    this->dataList.clear();
}



AppConfig* AppConfig::appConfig_ = nullptr;;
