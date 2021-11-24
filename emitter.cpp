#include "emitter.h"

Emitter::Emitter(QString identifier)
{
    this->pointsCat21 = QList<WGS84Coordinates>();
    this->pointsCat20 = QList<WGS84Coordinates>();
    this->pointsCat10 = QList<WGS84Coordinates>();
    this->timeStampsCat21 = QList<QTime>();
    this->timeStampsCat20 = QList<QTime>();
    this->timeStampsCat10 = QList<QTime>();

    this->identifier = identifier;
}

void Emitter::AddPoint(WGS84Coordinates point, QTime timeStamp, int category) {

    if (category == 10) {
        this->pointsCat10.append(point);
        this->timeStampsCat10.append(timeStamp);
    }

    else if (category == 20) {
        this->pointsCat20.append(point);
        this->timeStampsCat20.append(timeStamp);
    }

    else if (category == 21) {
        this->pointsCat21.append(point);
        this->timeStampsCat21.append(timeStamp);
    }
}

QString Emitter::GetIdentifier() {
    return identifier;
}

QTime Emitter::GetFirstReport() {

    QVector<QTime> firstTimeStamps = QVector<QTime>();

    if (timeStampsCat10.length() != 0) {
        firstTimeStamps.append(timeStampsCat10.first());
    }
    if (timeStampsCat20.length() != 0) {
        firstTimeStamps.append(timeStampsCat20.first());
    }
    if (timeStampsCat21.length() != 0) {
        firstTimeStamps.append(timeStampsCat21.first());
    }

    QTime currentFirst = firstTimeStamps.at(0);

    for (int i = 1; i < firstTimeStamps.length(); i++) {
        if (currentFirst > firstTimeStamps.at(i)) {
            currentFirst = firstTimeStamps.at(i);
        }
    }

    return currentFirst;

}

QTime Emitter::GetLastReport() {
    QVector<QTime> lastTimeStamps = QVector<QTime>();

    if (timeStampsCat10.length() != 0) {
        lastTimeStamps.append(timeStampsCat10.last());
    }
    if (timeStampsCat20.length() != 0) {
        lastTimeStamps.append(timeStampsCat20.last());
    }
    if (timeStampsCat21.length() != 0) {
        lastTimeStamps.append(timeStampsCat21.last());
    }

    QTime currentLast = lastTimeStamps.at(0);

    for (int i = 1; i < lastTimeStamps.length(); i++) {
        if (currentLast < lastTimeStamps.at(i)) {
            currentLast = lastTimeStamps.at(i);
        }
    }

    return currentLast;
}

