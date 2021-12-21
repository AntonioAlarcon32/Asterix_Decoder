#ifndef CAT21_H
#define CAT21_H

#include "QTime"

#include "datablock.h"
#include "utilities.h"
#include "hdr/appconfig.h"



class Cat21: public DataBlock
{
public:

    Cat21();
    ~Cat21();
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

    QString trAtp;
    QString trArc;
    QString trRc;
    QString trRab;
    QString trDcr;
    QString trGbs;
    QString trSim;
    QString trTst;
    QString trSaa;
    QString trCl;
    QString trIpc;
    QString trNogo;
    QString trCpr;
    QString trLdpj;
    QString trRcf;

    int trackNumber;

    char serviceIdentification;

    QTime timeOfApplicabilityForPosition;

    double wgs84latitude;
    double wgs84longitude;

    double wgs84latitudeHighRes;
    double wgs84longitudeHighRes;

    QTime timeOfApplicabilityForVelocity;

    QString asUnits;
    double asAirSpeed;

    bool tasRangeExceeded;
    double tasTrueAirSpeed;

    QString targetAddress;

    QTime timeOfMessageReceptionOfPosition;

    double timeOfMessageReceptionOfPositionHighRes;

    QTime timeOfMessageReceptionOfVelocity;

    double timeOfMessageReceptionOfVelocityHighRes;

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

    short miWindSpeed;
    short miWindDirection;
    short miTemperature;
    short miTurbulence;

    QString saSas;
    QString saSource;
    double saAltitude;

    QString fssaMv;
    QString fssaAh;
    QString fssaAm;
    double fssaAltitude;

    QString tiNav;
    QString tiNvb;

    QVector<QString> tiTca;
    QVector<QString> tiNc;
    QVector<unsigned char> tiTcpNumber;
    QVector<double> tiAltitude;
    QVector<double> tiLatitude;
    QVector<double> tiLongitude;
    QVector<QString> tiPointType;
    QVector<QString> tiTd;
    QVector<QString> tiTra;
    QVector<QString> tiToa;
    QVector<int> tiTov;
    QVector<double> tiTtr;

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

    QVector<QByteArray> modeSMBData;
    QVector<unsigned char> modeSStoreAddress;

    QString ararTyp;
    QString ararStyp;
    QString ararAra;
    QString ararRac;
    QString ararRat;
    QString ararMte;
    QString ararTti;
    QString ararTid;

    unsigned char receiverId;

    float daAOS;
    float daTRD;
    float daM3A;
    float daQI;
    float daTrI;
    float daMA;
    float daGH;
    float daFL;
    float daISSA;
    float daFSSA;
    float daAS;
    float daTAS;
    float daMH;
    float daBVR;
    float daGVR;
    float daGV;
    float daTAR;
    float daTaI;
    float daTS;
    float daMET;
    float daROA;
    float daARA;
    float daSCC;

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

    QVector<unsigned char> GetDataAgesDataItem();
    QVector<unsigned char> GetMetInformationDataItem();
    QVector<unsigned char> GetTrajectoryIntentDataItem();
};

#endif // CAT21_H
