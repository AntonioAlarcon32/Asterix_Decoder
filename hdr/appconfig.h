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

    void AddSensor(Sensor sensor);
    QList<short> GetSystemAreaCodes();
    QList<short> GetSystemIdCodes();
    void ClearSensors();
    Sensor GetSensorInfo(int uniqueId);
    void LoadXMLFile(QString path);
    void SaveXMLFile(QString path);
    void DeleteSensor(int uniqueId);
    QList<int>GetUniqueIds();


private:

    AppConfig();

    static AppConfig* appConfig_;
    QList<Sensor> sensorList_;

};

#endif // APPCONFIG_H
