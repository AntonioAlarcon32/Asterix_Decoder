#include "emitter.h"

Emitter::Emitter(QString identifier)
{
    this->points = QList<WGS84Coordinates>();
    this->timeStamps = QList<QTime>();
    this->identifier = identifier;
}

void Emitter::AddPoint(WGS84Coordinates point, QTime timeStamp) {
    this->points.append(point);
    this->timeStamps.append(timeStamp);
}

QString Emitter::GetIdentifier() {
    return identifier;
}

QTime Emitter::GetFirstReport() {
    return timeStamps.first();

}
QTime Emitter::GetLastReport() {
    return timeStamps.last();
}

