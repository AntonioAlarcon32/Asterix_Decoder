#ifndef CAT20_H
#define CAT20_H

#include "QTime"

#include "hdr/asterix_lib/datablock.h"
#include "hdr/asterix_lib/utilities.h"

class Cat20: public DataBlock
{
public:

    short systemAreaCode;
    short systemIdentificationCode;

    QString trSsr;
    QString trMs;
    QString trHf;
    QString trVdl4;
    QString trUat;
    QString trDme;
    QString trOt;
    QString trRab;
    QString trSpi;
    QString trChn;
    QString trGbs;
    QString trCrt;
    QString trSim;
    QString trTst;
    QString trCf;

    QTime timeOfDay;

    double wgs84latitude;
    double wgs84longitude;

    double cartesianX;
    double cartesianY;

    int trackNumber;

    QString tsCnf;
    QString tsTre;
    QString tsCst;
    QString tsCdm;
    QString tsMah;
    QString tsSth;
    QString tsGho;

    QString M3AValidated;
    QString M3AGarbled;
    QString M3ADerivation;
    QString M3ACode;

    double cartesianVx;
    double cartesianVy;

    QString flValidated;
    QString flGarbled;
    double flFlightLevel;

    QString ModeCCode; //REVISAR

    QString targetAddress;

    QString targetIdentification;

    double measuredHeight;

    double geometricHeight;

    double cartesianAx;
    double cartesianAy;

    QString VehicleFleetIdentification;

    QString ppmTrb;
    QString ppmMsg;

    QString positionAccuracy; //REVISAR

    QString contributingDevices; //REVISAR

    QString bdsRegisterData; //REVISAR

    QString cacfsCom;
    QString cacfsStat;
    QString cacfsMssc;
    QString cacfsArc;
    QString cacfsAic;
    QString cacfsB1A;
    QString cacfsB1B;

    QString acasReport; //REVISAR

    QVector<QString> errors;

    QString M1Validated;
    QString M1Garbled;
    QString M1Derivation;
    QString M1Code;

    QString M2Validated;
    QString M2Garbled;
    QString M2Derivation;
    QString M2Code;


    Cat20();
    void FullDecode();

    void DecodeDataSourceIdentifier(QVector<unsigned char> &dataItem);
        void DecodeTargetReportDescriptor(QVector<unsigned char> &dataItem);
        void DecodeTimeOfDay(QVector<unsigned char> &dataItem);
        void DecodePositionInWGS84Coordinates(QVector<unsigned char> &dataItem);
        void DecodePositionInCartesianCoordinates(QVector<unsigned char> &dataItem);
        void DecodeTrackNumber(QVector<unsigned char> &dataItem);
        void DecodeTrackStatus(QVector<unsigned char> &dataItem);
        void DecodeMode3ACodeInOctalRepresentation(QVector<unsigned char> &dataItem);
        void DecodeCalculatedTrackVelocityInCartesianCoordinates(QVector<unsigned char> &dataItem);
        void DecodeFlightLevelInBinaryRepresentation(QVector<unsigned char> &dataItem);
        void DecodeModeCCode(QVector<unsigned char> &dataItem);
        void DecodeTargetAddress(QVector<unsigned char> &dataItem);
        void DecodeTargetIdentification(QVector<unsigned char> &dataItem);
        void DecodeMeasuredHeight(QVector<unsigned char> &dataItem);
        void DecodeGeometricHeight(QVector<unsigned char> &dataItem);
        void DecodeCalculatedAcceleration(QVector<unsigned char> &dataItem);
        void DecodeVehicleFleetIdentification(QVector<unsigned char> &dataItem);
        void DecodePreProgrammedMessage(QVector<unsigned char> &dataItem);
        void DecodePositionAccuracy(QVector<unsigned char> &dataItem);
        void DecodeContributingDevices(QVector<unsigned char> &dataItem);
        void DecodeBDSRegisterData(QVector<unsigned char> &dataItem);
        void DecodeCommsACASCapabilityAndFlightStatus(QVector<unsigned char> &dataItem);
        void DecodeACASResolutionAdvisoryReport(QVector<unsigned char> &dataItem);
        void DecodeWarningErrorConditions(QVector<unsigned char> &dataItem);
        void DecodeMode1CodeInOctalRepresentation(QVector<unsigned char> &dataItem);
        void DecodeMode2CodeInOctalRepresentation(QVector<unsigned char> &dataItem);

};

#endif // CAT20_H
