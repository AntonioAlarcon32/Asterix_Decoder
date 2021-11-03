#ifndef APPCONFIG_H
#define APPCONFIG_H

#include "QMap"
#include "QVector"
#include "QXmlStreamReader"
#include "QFile"
#include "QDebug"
#include "QDir"

#include "sensor.h"

class AppConfig
{
public:

    static AppConfig* GetInstance();
    int GetValue();

    AppConfig(AppConfig &other) = delete;
    void operator=(const AppConfig &) = delete;

    void AddSensor(Sensor sensor, short systemAreaCode);
    QList<short> GetSystemAreaCodes();

    Sensor GetSensorInfo(short systemAreaCode);

    void SetInitialConfig();

private:

    AppConfig();

    static AppConfig* appConfig_;
    int value;

    void LoadXMLFile(QString path);

    QMap<short,Sensor> dataList;

    void TrackUse();

};

#endif // APPCONFIG_H
