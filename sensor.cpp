#include "sensor.h"


Sensor::Sensor() {

}


Sensor::Sensor(QString sensorId,double sensorLatitude,double sensorLongitude,QString sensorIp, int category) {

    this->sensorId = sensorId;
    this->sensorLatitude = sensorLatitude;
    this->sensorLongitude = sensorLongitude;
    this->sensorIp = sensorIp;
    this->category = category;
}




