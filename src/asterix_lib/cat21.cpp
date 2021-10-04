#include "hdr/asterix_lib/cat21.h"

Cat21::Cat21()
{
    this->category = 21;
    this->length = 0;

    this->systemAreaCode = 0;
    this->systemIdentificationCode = 0;

    this->trATP = "N/A";
    this->trARC = "N/A";
    this->trRC = "N/A";
    this->trRAB = "N/A";
    this->trDCR = "N/A";
    this->trGBS = "N/A";
    this->trSIM = "N/A";
    this->trTST = "N/A";
    this->trSAA = "N/A";
    this->trCL = "N/A";
    this->trIPC = "N/A";
    this->trNOGO = "N/A";
    this->trCPR = "N/A";
    this->trLDPJ = "N/A";
    this->trRCF = "N/A";

    this->trackNumber = -1;

    this->serviceIdentification = 1;

    this->timeOfApplicabilityForPosition = QTime();

    this->wgs84latitude = nan("");
    this->wgs84longitude = nan("");

    this->wgs84latitudeHighRes = nan("");
    this->wgs84longitudeHighRes = nan("");

    this->timeOfApplicabilityForVelocity = QTime();

    this->airSpeed = nan("");

    this->trueAirSpeed = nan("");

    this->targetAddress = "N/A";

    this->timeOfMessageReceptionOfPosition = QTime();

    this->timeOfMessageReceptionOfPositionHighRes = QTime();

    this->timeOfMessageReceptionOfVelocity = QTime();

    this->timeOfMessageReceptionOfVelocityHighRes = QTime();

    this->geometricHeight = nan("");

    this->qiNucrOrNacv = "N/A";
    this->qiNucpOrNic = "N/A";
    this->qiNicBaro = "N/A";
    this->qiSil = "N/A";
    this->qiNacp = "N/A";
    this->qiSilSupplement = "N/A";
    this->qiSda = "N/A";
    this->qiGva = "N/A";
    this->qiPic = "N/A";

    this->mvVns = "N/A";
    this->mvVn = "N/A";
    this->mvLtt = "N/A";

    this->m3ACode = "N/A";

    this->rollAngle = nan("");

    this->flightLevel = nan("");

    this->magneticHeading = nan("");

    this->tsIcf = "N/A";
    this->tsLnav = "N/A";
    this->tsPs = "N/A";
    this->tsSs = "N/A";

    this->bvrRangeExceeded = 0;
    this->bvrBarometricVerticalRate = nan("");

    this->gvrRangeExceeded = 0;
    this->gvrGeometricVerticalRate = nan("");

    this->agvRangeExceeded = 0;
    this->agvGroundSpeed = nan("");
    this->agvTrackAngle = nan("");

    this->trackAngleRate = nan("");

    this->timeOfReportTransmission = QTime();

    this->targetIdentification = "N/A";

    this->emitterCategory = "N/A";

    this->metInfo = "N/A"; //REVISAR

    this->saSas = "N/A";
    this->saSource = "N/A";
    this->saAltitude = nan("");

    this->fssaMv = "N/A";
    this->fssaAh = "N/A";
    this->fssaAm = "N/A";
    this->fssaAltitude = nan("");

    this->trajectoryIntent = "N/A"; //REVISAR

    this->serviceManagement = nan("");

    this->aosRa = "N/A";
    this->aosTc = "N/A";
    this->aosTs = "N/A";
    this->aosArv = "N/A";
    this->aosCdti = "N/A";
    this->aosNotTcas = "N/A";
    this->aosSa = "N/A";

    this->sccPoa = "N/A";
    this->sccCdti = "N/A";
    this->sccB2Low = "N/A";
    this->sccRas = "N/A";
    this->sccIdent = "N/A";
    this->sccLengthPlusWidth = "N/A";

    this->messageAmplitude = 1;

    this->ararTyp = "N/A";
    this->ararStyp = "N/A";
    this->ararAra = "N/A";
    this->ararRac = "N/A";
    this->ararRat = "N/A";
    this->ararMte = "N/A";
    this->ararTti = "N/A";
    this->ararTid = "N/A";

    this->receiverId = 1;

    this->dataAges = "N/A"; //REVISAR
}

void Cat21::FullDecode() {

    if (this->fspec.length() > 0) {

        if ((this->fspec.at(0) & 0x80) == 0x80) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeDataSourceIdentification(dataItem);
        }
        if ((this->fspec.at(0) & 0x40) == 0x40) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetVariableLengthDataItem(this->data);
            this->DecodeTargetReportDescriptor(dataItem);
        }
        if ((this->fspec.at(0) & 0x20) == 0x20) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeTrackNumber(dataItem);
        }
        if ((this->fspec.at(0) & 0x10) == 0x10) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1);
            this->DecodeServiceIdentification(dataItem);
        }
        if ((this->fspec.at(0) & 0x08) == 0x08) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,3);
            this->DecodeTimeOfApplicabilityForPosition(dataItem);
        }
        if ((this->fspec.at(0) & 0x04) == 0x04) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,6);
            this->DecodePositionInWGS84Coordinates(dataItem);
        }
        if ((this->fspec.at(0) & 0x02) == 0x02) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,8);
            this->DecodePositionInWGS84CoordinatesHighRes(dataItem);
        }
    }

    if (this->fspec.length() > 1) {

        if ((this->fspec.at(1) & 0x80) == 0x80) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,3);
            this->DecodeTimeOfApplicabilityForVelocity(dataItem);
        }
        if ((this->fspec.at(1) & 0x40) == 0x40) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeAirSpeed(dataItem);
        }
        if ((this->fspec.at(1) & 0x20) == 0x20) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeTrueAirSpeed(dataItem);
        }
        if ((this->fspec.at(1) & 0x10) == 0x10) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,3);
            this->DecodeTargetAddress(dataItem);
        }
        if ((this->fspec.at(1) & 0x08) == 0x08) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,3);
            this->DecodeTimeOfMessageReceptionOfPosition(dataItem);
        }
        if ((this->fspec.at(1) & 0x04) == 0x04) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,4);
            this->DecodeTimeOfMessageReceptionOfPositionHighPrecision(dataItem);
        }
        if ((this->fspec.at(1) & 0x02) == 0x02) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,3);
            this->DecodeTimeOfMessageReceptionOfVelocity(dataItem);
        }
    }
    if (this->fspec.length() > 2) {

        if ((this->fspec.at(2) & 0x80) == 0x80) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,4);
            this->DecodeTimeOfMessageReceptionOfVelocityHighPrecision(dataItem);
        }
        if ((this->fspec.at(2) & 0x40) == 0x40) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeGeometricHeight(dataItem);
        }
        if ((this->fspec.at(2) & 0x20) == 0x20) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetVariableLengthDataItem(this->data);
            this->DecodeQualityIndicators(dataItem);
        }
        if ((this->fspec.at(2) & 0x10) == 0x10) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1);
            this->DecodeMOPSVersion(dataItem);
        }
        if ((this->fspec.at(2) & 0x08) == 0x08) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeMode3ACode(dataItem);
        }
        if ((this->fspec.at(2) & 0x04) == 0x04) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeRollAngle(dataItem);
        }
        if ((this->fspec.at(2) & 0x02) == 0x02) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeFlightLevel(dataItem);
        }
    }
    if (this->fspec.length() > 3) {

        if ((this->fspec.at(3) & 0x80) == 0x80) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeMagneticHeading(dataItem);
        }
        if ((this->fspec.at(3) & 0x40) == 0x40) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1);
            this->DecodeTargetStatus(dataItem);
        }
        if ((this->fspec.at(3) & 0x20) == 0x20) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeBarometricVerticalRate(dataItem);
        }
        if ((this->fspec.at(3) & 0x10) == 0x10) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeGeometricVerticalRate(dataItem);
        }
        if ((this->fspec.at(3) & 0x08) == 0x08) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,4);
            this->DecodeAirborneGroundVector(dataItem);
        }
        if ((this->fspec.at(3) & 0x04) == 0x04) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeTrackAngleRate(dataItem);
        }
        if ((this->fspec.at(2) & 0x02) == 0x02) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,3);
            this->DecodeTimeOfReportTransmission(dataItem);
        }
    }

    if (this->fspec.length() > 4) {

        if ((this->fspec.at(3) & 0x80) == 0x80) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,6);
            this->DecodeTargetIdentification(dataItem);
        }
        if ((this->fspec.at(3) & 0x40) == 0x40) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1);
            this->DecodeEmitterCategory(dataItem);
        }
        if ((this->fspec.at(3) & 0x20) == 0x20) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetVariableLengthDataItem(this->data);
            this->DecodeMetInformation(dataItem);
        }
        if ((this->fspec.at(3) & 0x10) == 0x10) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeSelectedAltitude(dataItem);
        }
        if ((this->fspec.at(3) & 0x08) == 0x08) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeFinalStateSelectedAltitude(dataItem);
        }
        if ((this->fspec.at(3) & 0x04) == 0x04) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetVariableLengthDataItem(this->data);
            this->DecodeTrajectoryIntent(dataItem);
        }
        if ((this->fspec.at(2) & 0x02) == 0x02) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1);
            this->DecodeServiceManagement(dataItem);
        }
    }

    if (this->fspec.length() > 5) {

        if ((this->fspec.at(3) & 0x80) == 0x80) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1);
            this->DecodeAircraftOperationalStatus(dataItem);
        }
        if ((this->fspec.at(3) & 0x40) == 0x40) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetVariableLengthDataItem(this->data);
            this->DecodeSurfaceCapabilitiesAndCharacteristics(dataItem);
        }
        if ((this->fspec.at(3) & 0x20) == 0x20) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1);
            this->DecodeMessageAmplitude(dataItem);
        }
        if ((this->fspec.at(3) & 0x10) == 0x10) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetRepetitiveDataItem(this->data,8);
            this->DecodeModeSMBData(dataItem);
        }
        if ((this->fspec.at(3) & 0x08) == 0x08) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,7);
            this->DecodeACASResolutionAdvisoryReport(dataItem);
        }
        if ((this->fspec.at(3) & 0x04) == 0x04) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1);
            this->DecodeReceiverID(dataItem);
        }
        if ((this->fspec.at(2) & 0x02) == 0x02) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetVariableLengthDataItem(this->data);
            this->DecodeDataAges(dataItem);
        }
    }
}

void Cat21::DecodeDataSourceIdentification(QVector<unsigned char> &dataItem) {}
void Cat21::DecodeTargetReportDescriptor(QVector<unsigned char> &dataItem){}
void Cat21::DecodeTrackNumber(QVector<unsigned char> &dataItem){}
void Cat21::DecodeServiceIdentification(QVector<unsigned char> &dataItem){}
void Cat21::DecodeTimeOfApplicabilityForPosition(QVector<unsigned char> &dataItem){}
void Cat21::DecodePositionInWGS84Coordinates(QVector<unsigned char> &dataItem){}
void Cat21::DecodePositionInWGS84CoordinatesHighRes(QVector<unsigned char> &dataItem){}
void Cat21::DecodeTimeOfApplicabilityForVelocity(QVector<unsigned char> &dataItem){}
void Cat21::DecodeAirSpeed(QVector<unsigned char> &dataItem){}
void Cat21::DecodeTrueAirSpeed(QVector<unsigned char> &dataItem){}
void Cat21::DecodeTargetAddress(QVector<unsigned char> &dataItem){}
void Cat21::DecodeTimeOfMessageReceptionOfPosition(QVector<unsigned char> &dataItem){}
void Cat21::DecodeTimeOfMessageReceptionOfPositionHighPrecision(QVector<unsigned char> &dataItem){}
void Cat21::DecodeTimeOfMessageReceptionOfVelocity(QVector<unsigned char> &dataItem){}
void Cat21::DecodeTimeOfMessageReceptionOfVelocityHighPrecision(QVector<unsigned char> &dataItem){}
void Cat21::DecodeGeometricHeight(QVector<unsigned char> &dataItem){}
void Cat21::DecodeQualityIndicators(QVector<unsigned char> &dataItem){}
void Cat21::DecodeMOPSVersion(QVector<unsigned char> &dataItem){}
void Cat21::DecodeMode3ACode(QVector<unsigned char> &dataItem){}
void Cat21::DecodeRollAngle(QVector<unsigned char> &dataItem){}
void Cat21::DecodeFlightLevel(QVector<unsigned char> &dataItem){}
void Cat21::DecodeMagneticHeading(QVector<unsigned char> &dataItem){}
void Cat21::DecodeTargetStatus(QVector<unsigned char> &dataItem){}
void Cat21::DecodeBarometricVerticalRate(QVector<unsigned char> &dataItem){}
void Cat21::DecodeGeometricVerticalRate(QVector<unsigned char> &dataItem){}
void Cat21::DecodeAirborneGroundVector(QVector<unsigned char> &dataItem){}
void Cat21::DecodeTrackAngleRate(QVector<unsigned char> &dataItem){}
void Cat21::DecodeTimeOfReportTransmission(QVector<unsigned char> &dataItem){}
void Cat21::DecodeTargetIdentification(QVector<unsigned char> &dataItem){}
void Cat21::DecodeEmitterCategory(QVector<unsigned char> &dataItem){}
void Cat21::DecodeMetInformation(QVector<unsigned char> &dataItem){}
void Cat21::DecodeSelectedAltitude(QVector<unsigned char> &dataItem){}
void Cat21::DecodeFinalStateSelectedAltitude(QVector<unsigned char> &dataItem){}
void Cat21::DecodeTrajectoryIntent(QVector<unsigned char> &dataItem){}
void Cat21::DecodeServiceManagement(QVector<unsigned char> &dataItem){}
void Cat21::DecodeAircraftOperationalStatus(QVector<unsigned char> &dataItem){}
void Cat21::DecodeSurfaceCapabilitiesAndCharacteristics(QVector<unsigned char> &dataItem){}
void Cat21::DecodeMessageAmplitude(QVector<unsigned char> &dataItem){}
void Cat21::DecodeModeSMBData(QVector<unsigned char> &dataItem){}
void Cat21::DecodeACASResolutionAdvisoryReport(QVector<unsigned char> &dataItem){}
void Cat21::DecodeReceiverID(QVector<unsigned char> &dataItem){}
void Cat21::DecodeDataAges(QVector<unsigned char> &dataItem){}
