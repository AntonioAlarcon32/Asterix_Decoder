#include "hdr/asterix_lib/sensor.h"


Sensor::Sensor() {
    this->uniqueId = 0;
}


Sensor::Sensor(QString description,double sensorLatitude,double sensorLongitude,QString sensorIp, int category,short systemIdCode, short systemAreaCode, int port) {

    this->uniqueId = rand();
    this->sensorDescription = description;
    this->sensorLatitude = sensorLatitude;
    this->sensorLongitude = sensorLongitude;
    this->sensorIp = sensorIp;
    this->category = category;
    this->systemAreaCode = systemAreaCode;
    this->systemIdCode = systemIdCode;
    this->port = port;
}

Sensor::Sensor(int uniqueId, QString description,double sensorLatitude,double sensorLongitude,QString sensorIp, int category,short systemIdCode, short systemAreaCode, int port) {

    this->uniqueId = uniqueId;
    this->sensorDescription = description;
    this->sensorLatitude = sensorLatitude;
    this->sensorLongitude = sensorLongitude;
    this->sensorIp = sensorIp;
    this->category = category;
    this->systemAreaCode = systemAreaCode;
    this->systemIdCode = systemIdCode;
    this->port = port;
}

void Sensor::AssignUniqueId() {
    if (uniqueId == 0) {
        this->uniqueId = rand();
    }
}




