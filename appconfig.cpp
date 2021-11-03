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

void AppConfig::TrackUse() {
    this->value++;
}

int AppConfig::GetValue() {
    this->TrackUse();
    return this->value;
}

QList<short> AppConfig::GetSystemAreaCodes() {
    return this->dataList.keys();
}

void AppConfig::AddSensor(Sensor sensor, short systemAreaCode) {

    this->dataList.insert(systemAreaCode, sensor);

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

void AppConfig::SetInitialConfig() {

    this->LoadXMLFile("/Users/antonioalarcon/Documents/TFG/xml_config");

}

AppConfig* AppConfig::appConfig_ = nullptr;;
