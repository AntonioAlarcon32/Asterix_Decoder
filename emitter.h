#ifndef EMITTER_H
#define EMITTER_H


#include "QList"
#include "QString"
#include "QTime"
#include "hdr/asterix_lib/utilities.h"
#include "wgs84coordinates.h"

class Emitter
{
public:
    Emitter(QString id);

    QString GetIdentifier();
    void AddPoint(WGS84Coordinates point, QTime timeStamp, int category);

    QTime GetFirstReport();
    QTime GetLastReport();

private:
    QString identifier;
    QList<WGS84Coordinates> pointsCat21;
    QList<WGS84Coordinates> pointsCat20;
    QList<WGS84Coordinates> pointsCat10;

    QList<QTime> timeStampsCat21;
    QList<QTime> timeStampsCat20;
    QList<QTime> timeStampsCat10;
};

#endif // EMITTER_H
