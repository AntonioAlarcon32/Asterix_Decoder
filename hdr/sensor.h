#ifndef SENSOR_H
#define SENSOR_H

#include "QString"


class Sensor
{
public:

    Sensor();

    Sensor(QString sensorId,double sensorLatitude,double sensorLongitude,QString sensorIp,int category,short systemIdCode, short systemAreaCode);
    Sensor(int uniqueId, QString sensorId,double sensorLatitude,double sensorLongitude,QString sensorIp,int category,short systemIdCode, short systemAreaCode);

    int uniqueId;
    QString sensorDescription;
    double sensorLatitude;
    double sensorLongitude;
    QString sensorIp;
    int category;
    short systemAreaCode;
    short systemIdCode;

    void AssignUniqueId();
};

#endif // SENSOR_H
