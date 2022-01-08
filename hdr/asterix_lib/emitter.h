#ifndef EMITTER_H
#define EMITTER_H


#include "QList"
#include "QString"
#include "QTime"
#include "utilities.h"
#include "wgs84coordinates.h"

class Emitter
{
public:
    Emitter(QString id, QString detectedEmission);

    QString GetCallSign();
    QString GetTargetAddress();
    QString GetTrackNumber();
    QString GetMode3ACode();
    QList<QString> GetDetectedEmissions();

    void SetCallSign(QString callSign);
    void SetTrackNumber(QString trackNumber);
    void SetMode3ACode(QString mode3ACode);

    void AddPoint(WGS84Coordinates point, QTime timeStamp, int category, QString typeOfEmission);

    QTime GetFirstReport();
    QTime GetLastReport();

    QList<WGS84Coordinates> pointsCat21;
    QList<WGS84Coordinates> pointsCat20;
    QList<WGS84Coordinates> pointsCat10Mlat;
    QList<WGS84Coordinates> pointsCat10Smr;
    QList<QTime> timeStampsCat21;
    QList<QTime> timeStampsCat20;
    QList<QTime> timeStampsCat10Mlat;
    QList<QTime> timeStampsCat10Smr;

private:
    QString callSign;
    QString targetAddress;
    QString trackNumber;
    QString mode3ACode;
    QList<QString> detectedEmissions;
};

#endif // EMITTER_H
