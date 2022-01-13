#include "hdr/asterix_lib/emitter.h"

Emitter::Emitter(QString targetAddress, QString detectedEmission)
{
    this->pointsCat21 = QList<WGS84Coordinates>();
    this->pointsCat20 = QList<WGS84Coordinates>();
    this->pointsCat10Mlat = QList<WGS84Coordinates>();          //Lists of points for all categories
    this->pointsCat10Smr = QList<WGS84Coordinates>();
    this->timeStampsCat21 = QList<QTime>();
    this->timeStampsCat20 = QList<QTime>();
    this->timeStampsCat10Mlat = QList<QTime>();                 //List of timestamps for all categories
    this->timeStampsCat10Smr = QList<QTime>();
    this->detectedEmissions = QList<QString>();         //List of detected categories of this emitter

    this->targetAddress = targetAddress;                //Set the address
    this->trackNumber = "N/A";
    this->callSign = "N/A";
    this->mode3ACode = "N/A";

    this->detectedEmissions.append(detectedEmission);       //Add the detected emission when created

}

void Emitter::AddPoint(WGS84Coordinates point, QTime timeStamp, int category, QString typeOfEmission) {

    if (detectedEmissions.indexOf(typeOfEmission) == -1) {
        detectedEmissions.append(typeOfEmission);               //Search if the detected emission exists, if not, add it
    }

    if (category == 10 && typeOfEmission == "CAT 10: PSR") {
        this->pointsCat10Smr.append(point);                     //For CAT10, separate SMR and MLAT
        this->timeStampsCat10Smr.append(timeStamp);
    }

    else if (category == 10 && typeOfEmission != "CAT 10: PSR") {
        this->pointsCat10Mlat.append(point);
        this->timeStampsCat10Mlat.append(timeStamp);
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

QString Emitter::GetTargetAddress() {
    return targetAddress;
}

QString Emitter::GetCallSign() {
    return callSign;
}

QString Emitter::GetMode3ACode() {
    return mode3ACode;
}

QString Emitter::GetTrackNumber() {
    return trackNumber;
}

void Emitter::SetCallSign(QString callSign) {
    this->callSign = callSign;
}

void Emitter::SetMode3ACode(QString mode3ACode) {
    this->mode3ACode = mode3ACode;
}

void Emitter::SetTrackNumber(QString trackNumber) {
    this->trackNumber = trackNumber;
}


QTime Emitter::GetFirstReport() {

    QVector<QTime> firstTimeStamps = QVector<QTime>();

    if (timeStampsCat10Smr.length() != 0) {
        firstTimeStamps.append(timeStampsCat10Smr.first());
    }
    if (timeStampsCat10Mlat.length() != 0) {
        firstTimeStamps.append(timeStampsCat10Mlat.first());
    }
    if (timeStampsCat20.length() != 0) {
        firstTimeStamps.append(timeStampsCat20.first());
    }
    if (timeStampsCat21.length() != 0) {
        firstTimeStamps.append(timeStampsCat21.first());                //Create a list with the first timestamp of each category
    }

    QTime currentFirst = firstTimeStamps.at(0);

    for (int i = 1; i < firstTimeStamps.length(); i++) {
        if (currentFirst > firstTimeStamps.at(i)) {
            currentFirst = firstTimeStamps.at(i);                   //Loop the list to see which one is the first
        }
    }

    return currentFirst;

}

QTime Emitter::GetLastReport() {
    QVector<QTime> lastTimeStamps = QVector<QTime>();

    if (timeStampsCat10Smr.length() != 0) {
        lastTimeStamps.append(timeStampsCat10Smr.last());
    }
    if (timeStampsCat10Mlat.length() != 0) {
        lastTimeStamps.append(timeStampsCat10Mlat.last());
    }
    if (timeStampsCat20.length() != 0) {
        lastTimeStamps.append(timeStampsCat20.last());
    }
    if (timeStampsCat21.length() != 0) {
        lastTimeStamps.append(timeStampsCat21.last());
    }

    QTime currentLast = lastTimeStamps.at(0);

    for (int i = 1; i < lastTimeStamps.length(); i++) {
        if (currentLast < lastTimeStamps.at(i)) {                   //Same as before, but for latest emission
            currentLast = lastTimeStamps.at(i);
        }
    }

    return currentLast;
}

QList<QString> Emitter::GetDetectedEmissions() {
    return this->detectedEmissions;
}

