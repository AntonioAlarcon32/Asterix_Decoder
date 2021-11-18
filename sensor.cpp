#include "sensor.h"


Sensor::Sensor() {
    this->uniqueId = 0;
}


Sensor::Sensor(QString description,double sensorLatitude,double sensorLongitude,QString sensorIp, int category,short systemIdCode, short systemAreaCode) {

    this->uniqueId = arc4random();
    this->sensorDescription = description;
    this->sensorLatitude = sensorLatitude;
    this->sensorLongitude = sensorLongitude;
    this->sensorIp = sensorIp;
    this->category = category;
    this->systemAreaCode = systemAreaCode;
    this->systemIdCode = systemIdCode;
}

Sensor::Sensor(int uniqueId, QString description,double sensorLatitude,double sensorLongitude,QString sensorIp, int category,short systemIdCode, short systemAreaCode) {

    this->uniqueId = uniqueId;
    this->sensorDescription = description;
    this->sensorLatitude = sensorLatitude;
    this->sensorLongitude = sensorLongitude;
    this->sensorIp = sensorIp;
    this->category = category;
    this->systemAreaCode = systemAreaCode;
    this->systemIdCode = systemIdCode;
}

void Sensor::AssignUniqueId() {
    if (uniqueId == 0) {
        this->uniqueId = arc4random();
    }
}




