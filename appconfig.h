#ifndef APPCONFIG_H
#define APPCONFIG_H

#include "QMap"
#include "QVector"
#include "QXmlStreamReader"
#include "QFile"
#include "QDebug"

#include "sensor.h"

class AppConfig
{
public:

    static AppConfig* GetInstance();

    AppConfig(AppConfig &other) = delete;
    void operator=(const AppConfig &) = delete;

    void AddSensor(Sensor sensor, short systemAreaCode);
    QList<short> GetSystemAreaCodes();
    Sensor GetSensorInfo(short systemAreaCode);
    void LoadXMLFile(QString path);
    void SaveXMLFile(QString path);
    void DeleteSensor(short systemAreaCode);


private:

    AppConfig();

    static AppConfig* appConfig_;
    int value;
    QMap<short,Sensor> dataList;


};

#endif // APPCONFIG_H
