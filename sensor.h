#ifndef SENSOR_H
#define SENSOR_H

#include "QString"


class Sensor
{
public:

    Sensor();

    Sensor(QString sensorId,double sensorLatitude,double sensorLongitude,QString sensorIp,int category);

    QString sensorId;
    double sensorLatitude;
    double sensorLongitude;
    QString sensorIp;
    int category;
};

#endif // SENSOR_H
