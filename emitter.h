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
    void AddPoint(WGS84Coordinates point, QTime timeStamp);

    QTime GetFirstReport();
    QTime GetLastReport();

private:
    QString identifier;
    QList<WGS84Coordinates> points;
    QList<QTime> timeStamps;
};

#endif // EMITTER_H
