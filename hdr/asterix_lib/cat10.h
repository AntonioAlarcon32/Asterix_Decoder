#ifndef CAT10_H
#define CAT10_H

#include "QTime"

#include "hdr/asterix_lib/datablock.h"
#include "hdr/asterix_lib/utilities.h"


class Cat10: public DataBlock
{
public:

    short systemAreaCode;
    short systemIdentificationCode;

    QString typeOfMessage;

    QString trTYP;
    QString trDCR;
    QString trCHN;
    QString trGBS;
    QString trCRT;
    QString trSIM;
    QString trTST;
    QString trRAB;
    QString trLOP;
    QString trTOT;
    QString trSPI;

    QTime timeOfDay;

    double wgs84latitude;
    double wgs84longitude;

    double polarRho;
    double polarTheta;

    double cartesianX;
    double cartesianY;

    QString M3AValidated;
    QString M3AGarbled;
    QString M3ADerivation;
    QString M3ACode;

    QString targetAddress;

    QString targetIdentification;

    double polarGroundSpeed;
    double polarTrackAngle;

    double cartesianVx;
    double cartesianVy;

    int trackNumber;

    QString tsCNF;
    QString tsTRE;
    QString tsCST;
    QString tsMAH;
    QString tsTCC;
    QString tsSTH;
    QString tsTOM;
    QString tsDOU;
    QString tsMRS;
    QString tsGHO;

    QString flValidated;
    QString flGarbled;
    double flFlightLevel;

    double targetLength;
    double targetOrientation;
    double targetWidth;

    double calcAccelerationX;
    double calcAccelerationY;

    QString ssNOGO;
    QString ssOVL;
    QString ssTSV;
    QString ssDIV;
    QString ssTTF;

    QString vehicleFleetId;

    double measuredHeight;

    QString ppmTRB;
    QString ppMSG;

    double standardDeviationX;
    double standardDeviationY;
    double standardDeviationXY;

    double amplitudeOfPrimaryPlot;

    Cat10();
    void FullDecode();

    void DecodeDataSourceIdentifier(QVector<char> &dataItem);
    void DecodeMessageType(QVector<char> &dataItem);
    void DecodeTargetReportDescriptor(QVector<char> &dataItem);
    void DecodeTimeOfDay(QVector<char> &dataItem);
    void DecodePositionInWGS84Coordinates(QVector<char> &dataItem);
    void DecodeMeasuredPositionInPolarCoordinates(QVector<char> &dataItem);
    void DecodePositionInCartesianCoordinates(QVector<char> &dataItem);
    void DecodeCalculatedTrackVelocityInPolarCoordinates(QVector<char> &dataItem);
    void DecodeCalculatedTrackVelocityInCartesianCoordinates(QVector<char> &dataItem);
    void DecodeTrackNumber(QVector<char> &dataItem);
    void DecodeTrackStatus(QVector<char> &dataItem);
    void DecodeMode3ACodeInOctalRepresentation(QVector<char> &dataItem);
    void DecodeTargetAddress(QVector<char> &dataItem);
    void DecodeTargetIdentification(QVector<char> &dataItem);
    void DecodeModeSMBData(QVector<char> &dataItem);
    void DecodeVehicleFleetIdentification(QVector<char> &dataItem);
    void DecodeFlightLevelInBinaryRepresentation(QVector<char> &dataItem);
    void DecodeMeasuredHeight(QVector<char> &dataItem);
    void DecodeTargetSizeAndOrientation(QVector<char> &dataItem);
    void DecodeSystemStatus(QVector<char> &dataItem);
    void DecodePreProgrammedMessage(QVector<char> &dataItem);
    void DecodeStandardDeviationOfPosition(QVector<char> &dataItem);
    void DecodePresence(QVector<char> &dataItem);
    void DecodeAmplitudeOfPrimaryPlot(QVector<char> &dataItem);
    void DecodeCalculatedAcceleration(QVector<char> &dataItem);
    void DecodeSpecialPurposeField(QVector<char> &dataItem);

};

#endif // CAT10_H
