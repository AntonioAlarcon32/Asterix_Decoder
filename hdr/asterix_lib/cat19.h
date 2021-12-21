#ifndef CAT19_H
#define CAT19_H

#include "QTime"


#include "datablock.h"
#include "utilities.h"
#include "hdr/appconfig.h"

class Cat19: public DataBlock
{
public:

    Cat19();
        ~Cat19();
    void FullDecode();
    QString GetTypeOfMessage();
    QTime GetTimeOfReception();
    QString GetSACSIC();
    WGS84Coordinates GetPosition();
    QString GetIdentifier();
    QString GetCallSign();
    QString GetAddress();
    QString GetTrackNumber();
    QString GetMode3A();
    QTreeWidgetItem* GetPacketInfo();
    QString GetTypeOfTransmission();

private:

    short systemAreaCode;
    short systemIdentificationCode;

    QString typeOfMessage;

    QTime timeOfDay;

    QString ssNogo;
    QString ssOvl;
    QString ssTsv;
    QString ssTtf;

    QString tp1Status;
    QString tp2Status;
    QString tp3Status;
    QString tp4Status;

    QVector<unsigned char> rsIds;
    QVector<QString> rsTypes;
    QVector<QString> rsOperationals;


    QString rt1Status;
    QString rt2Status;
    QString rt3Status;
    QString rt4Status;

    double wgs84latitude;
    double wgs84longitude;

    double wgs84height;

    char wgs84undulation;


    void DecodeDataSourceIdentifier(QVector<unsigned char> &dataItem);
    void DecodeMessageType(QVector<unsigned char> &dataItem);
    void DecodeTimeOfDay(QVector<unsigned char> &dataItem);
    void DecodeSystemStatus(QVector<unsigned char> &dataItem);
    void DecodeTrackingProcessorDetailedStatus(QVector<unsigned char> &dataItem);
    void DecodeRemoteSensorDetailedStatus(QVector<unsigned char> &dataItem);
    void DecodeReferenceTrasponderDetailedStatus(QVector<unsigned char> &dataItem);
    void DecodePositionOfTheMLTSystemReferencePoint(QVector<unsigned char> &dataItem);
    void DecodeHeightOfTheMLTSystemReferencePoint(QVector<unsigned char> &dataItem);
    void DecodeWGS84Undulation(QVector<unsigned char> &dataItem);
};

#endif // CAT19_H
