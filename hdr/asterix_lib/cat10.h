#ifndef CAT10_H
#define CAT10_H

#include "QTime"

#include "hdr/asterix_lib/datablock.h"
#include "hdr/asterix_lib/utilities.h"
#include "hdr/appconfig.h"



class Cat10: public DataBlock
{
public:

    Cat10();
    ~Cat10();
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

    QVector<QByteArray> modeSMBData;
    QVector<unsigned char> modeSStoreAddress;

    QString vehicleFleetId;

    double measuredHeight;

    QString ppmTRB;
    QString ppMSG;

    double standardDeviationX;
    double standardDeviationY;
    double standardDeviationXY;

    QVector<unsigned char> presenceDRho;
    QVector<unsigned char> presenceDTheta;

    double amplitudeOfPrimaryPlot;

    void DecodeDataSourceIdentifier(QVector<unsigned char> &dataItem);
    void DecodeMessageType(QVector<unsigned char> &dataItem);
    void DecodeTargetReportDescriptor(QVector<unsigned char> &dataItem);
    void DecodeTimeOfDay(QVector<unsigned char> &dataItem);
    void DecodePositionInWGS84Coordinates(QVector<unsigned char> &dataItem);
    void DecodeMeasuredPositionInPolarCoordinates(QVector<unsigned char> &dataItem);
    void DecodePositionInCartesianCoordinates(QVector<unsigned char> &dataItem);
    void DecodeCalculatedTrackVelocityInPolarCoordinates(QVector<unsigned char> &dataItem);
    void DecodeCalculatedTrackVelocityInCartesianCoordinates(QVector<unsigned char> &dataItem);
    void DecodeTrackNumber(QVector<unsigned char> &dataItem);
    void DecodeTrackStatus(QVector<unsigned char> &dataItem);
    void DecodeMode3ACodeInOctalRepresentation(QVector<unsigned char> &dataItem);
    void DecodeTargetAddress(QVector<unsigned char> &dataItem);
    void DecodeTargetIdentification(QVector<unsigned char> &dataItem);
    void DecodeModeSMBData(QVector<unsigned char> &dataItem);
    void DecodeVehicleFleetIdentification(QVector<unsigned char> &dataItem);
    void DecodeFlightLevelInBinaryRepresentation(QVector<unsigned char> &dataItem);
    void DecodeMeasuredHeight(QVector<unsigned char> &dataItem);
    void DecodeTargetSizeAndOrientation(QVector<unsigned char> &dataItem);
    void DecodeSystemStatus(QVector<unsigned char> &dataItem);
    void DecodePreProgrammedMessage(QVector<unsigned char> &dataItem);
    void DecodeStandardDeviationOfPosition(QVector<unsigned char> &dataItem);
    void DecodePresence(QVector<unsigned char> &dataItem);
    void DecodeAmplitudeOfPrimaryPlot(QVector<unsigned char> &dataItem);
    void DecodeCalculatedAcceleration(QVector<unsigned char> &dataItem);
    void DecodeSpecialPurposeField(QVector<unsigned char> &dataItem);

};

#endif // CAT10_H
