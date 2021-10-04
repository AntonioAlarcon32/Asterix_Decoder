#ifndef CAT21_H
#define CAT21_H

#include "QTime"

#include "hdr/asterix_lib/datablock.h"
#include "hdr/asterix_lib/utilities.h"


class Cat21: public DataBlock
{
public:

    short systemAreaCode;
    short systemIdentificationCode;

    QString trATP;
    QString trARC;
    QString trRC;
    QString trRAB;
    QString trDCR;
    QString trGBS;
    QString trSIM;
    QString trTST;
    QString trSAA;
    QString trCL;
    QString trIPC;
    QString trNOGO;
    QString trCPR;
    QString trLDPJ;
    QString trRCF;

    int trackNumber;

    char serviceIdentification;

    QTime timeOfApplicabilityForPosition;

    double wgs84latitude;
    double wgs84longitude;

    double wgs84latitudeHighRes;
    double wgs84longitudeHighRes;

    QTime timeOfApplicabilityForVelocity;

    double airSpeed;

    double trueAirSpeed;

    QString targetAddress;

    QTime timeOfMessageReceptionOfPosition;

    QTime timeOfMessageReceptionOfPositionHighRes;

    QTime timeOfMessageReceptionOfVelocity;

    QTime timeOfMessageReceptionOfVelocityHighRes;

    double geometricHeight;

    QString qiNucrOrNacv;
    QString qiNucpOrNic;
    QString qiNicBaro;
    QString qiSil;
    QString qiNacp;
    QString qiSilSupplement;
    QString qiSda;
    QString qiGva;
    QString qiPic;

    QString mvVns;
    QString mvVn;
    QString mvLtt;

    QString m3ACode;

    double rollAngle;

    double flightLevel;

    double magneticHeading;

    QString tsIcf;
    QString tsLnav;
    QString tsPs;
    QString tsSs;

    bool bvrRangeExceeded;
    double bvrBarometricVerticalRate;

    bool gvrRangeExceeded;
    double gvrGeometricVerticalRate;

    bool agvRangeExceeded;
    double agvGroundSpeed;
    double agvTrackAngle;

    double trackAngleRate;

    QTime timeOfReportTransmission;

    QString targetIdentification;

    QString emitterCategory;

    QString metInfo; //REVISAR

    QString saSas;
    QString saSource;
    double saAltitude;

    QString fssaMv;
    QString fssaAh;
    QString fssaAm;
    double fssaAltitude;

    QString trajectoryIntent; //REVISAR

    double serviceManagement;

    QString aosRa;
    QString aosTc;
    QString aosTs;
    QString aosArv;
    QString aosCdti;
    QString aosNotTcas;
    QString aosSa;

    QString sccPoa;
    QString sccCdti;
    QString sccB2Low;
    QString sccRas;
    QString sccIdent;
    QString sccLengthPlusWidth;

    char messageAmplitude;

    QString ararTyp;
    QString ararStyp;
    QString ararAra;
    QString ararRac;
    QString ararRat;
    QString ararMte;
    QString ararTti;
    QString ararTid;

    char receiverId;

    QString dataAges; //REVISAR

    Cat21();
    void FullDecode();

    void DecodeDataSourceIdentification(QVector<unsigned char> &dataItem);
    void DecodeTargetReportDescriptor(QVector<unsigned char> &dataItem);
    void DecodeTrackNumber(QVector<unsigned char> &dataItem);
    void DecodeServiceIdentification(QVector<unsigned char> &dataItem);
    void DecodeTimeOfApplicabilityForPosition(QVector<unsigned char> &dataItem);
    void DecodePositionInWGS84Coordinates(QVector<unsigned char> &dataItem);
    void DecodePositionInWGS84CoordinatesHighRes(QVector<unsigned char> &dataItem);
    void DecodeTimeOfApplicabilityForVelocity(QVector<unsigned char> &dataItem);
    void DecodeAirSpeed(QVector<unsigned char> &dataItem);
    void DecodeTrueAirSpeed(QVector<unsigned char> &dataItem);
    void DecodeTargetAddress(QVector<unsigned char> &dataItem);
    void DecodeTimeOfMessageReceptionOfPosition(QVector<unsigned char> &dataItem);
    void DecodeTimeOfMessageReceptionOfPositionHighPrecision(QVector<unsigned char> &dataItem);
    void DecodeTimeOfMessageReceptionOfVelocity(QVector<unsigned char> &dataItem);
    void DecodeTimeOfMessageReceptionOfVelocityHighPrecision(QVector<unsigned char> &dataItem);
    void DecodeGeometricHeight(QVector<unsigned char> &dataItem);
    void DecodeQualityIndicators(QVector<unsigned char> &dataItem);
    void DecodeMOPSVersion(QVector<unsigned char> &dataItem);
    void DecodeMode3ACode(QVector<unsigned char> &dataItem);
    void DecodeRollAngle(QVector<unsigned char> &dataItem);
    void DecodeFlightLevel(QVector<unsigned char> &dataItem);
    void DecodeMagneticHeading(QVector<unsigned char> &dataItem);
    void DecodeTargetStatus(QVector<unsigned char> &dataItem);
    void DecodeBarometricVerticalRate(QVector<unsigned char> &dataItem);
    void DecodeGeometricVerticalRate(QVector<unsigned char> &dataItem);
    void DecodeAirborneGroundVector(QVector<unsigned char> &dataItem);
    void DecodeTrackAngleRate(QVector<unsigned char> &dataItem);
    void DecodeTimeOfReportTransmission(QVector<unsigned char> &dataItem);
    void DecodeTargetIdentification(QVector<unsigned char> &dataItem);
    void DecodeEmitterCategory(QVector<unsigned char> &dataItem);
    void DecodeMetInformation(QVector<unsigned char> &dataItem);
    void DecodeSelectedAltitude(QVector<unsigned char> &dataItem);
    void DecodeFinalStateSelectedAltitude(QVector<unsigned char> &dataItem);
    void DecodeTrajectoryIntent(QVector<unsigned char> &dataItem);
    void DecodeServiceManagement(QVector<unsigned char> &dataItem);
    void DecodeAircraftOperationalStatus(QVector<unsigned char> &dataItem);
    void DecodeSurfaceCapabilitiesAndCharacteristics(QVector<unsigned char> &dataItem);
    void DecodeMessageAmplitude(QVector<unsigned char> &dataItem);
    void DecodeModeSMBData(QVector<unsigned char> &dataItem);
    void DecodeACASResolutionAdvisoryReport(QVector<unsigned char> &dataItem);
    void DecodeReceiverID(QVector<unsigned char> &dataItem);
    void DecodeDataAges(QVector<unsigned char> &dataItem);
};

#endif // CAT21_H
