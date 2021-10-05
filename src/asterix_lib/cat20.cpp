#include "hdr/asterix_lib/cat20.h"

Cat20::Cat20()
{
    this->category = 20;
    this->length = 0;

    this->systemAreaCode = 0;
    this->systemIdentificationCode = 0;

    this->trSsr = "N/A";
    this->trMs = "N/A";
    this->trHf = "N/A";
    this->trVdl4 = "N/A";
    this->trUat = "N/A";
    this->trDme = "N/A";
    this->trOt = "N/A";
    this->trRab = "N/A";
    this->trSpi = "N/A";
    this->trChn = "N/A";
    this->trGbs = "N/A";
    this->trCrt = "N/A";
    this->trSim = "N/A";
    this->trTst = "N/A";
    this->trCf = "N/A";

    this->timeOfDay = QTime();

    this->wgs84latitude = nan("");
    this->wgs84longitude = nan("");

    this->cartesianX = nan("");
    this->cartesianY = nan("");

    this->trackNumber = -1;

    this->tsCnf = "N/A";
    this->tsTre = "N/A";
    this->tsCst = "N/A";
    this->tsCdm = "N/A";
    this->tsMah = "N/A";
    this->tsSth = "N/A";
    this->tsGho = "N/A";

    this->M3AValidated = "N/A";
    this->M3AGarbled = "N/A";
    this->M3ADerivation = "N/A";
    this->M3ACode = "N/A";

    this->cartesianVx = nan("");
    this->cartesianVy = nan("");

    this->flValidated = "N/A";
    this->flGarbled = "N/A";
    this->flFlightLevel = nan("");

    this->ModeCCode = "N/A"; //REVISA ;

    this->targetAddress = "N/A";

    this->targetIdentification = "N/A";

    this->measuredHeight = nan("");

    this->geometricHeight = nan("");

    this->cartesianAx = nan("");
    this->cartesianAy = nan("");

    this->VehicleFleetIdentification = "N/A";

    this->ppmTrb = "N/A";
    this->ppmMsg = "N/A";

    this->positionAccuracy = "N/A"; //REVISA =;

    this->contributingDevices = "N/A"; //REVISA ;

    this->bdsRegisterData = "N/A"; //REVISA ;

    this->cacfsCom = "N/A";
    this->cacfsStat = "N/A";
    this->cacfsMssc = "N/A";
    this->cacfsArc = "N/A";
    this->cacfsAic = "N/A";
    this->cacfsB1A = "N/A";
    this->cacfsB1B = "N/A";

    this->acasReport = "N/A"; //REVISA = "N/A";

    this->M1Validated = "N/A";
    this->M1Garbled = "N/A";
    this->M1Derivation = "N/A";
    this->M1Code = "N/A";

    this->M2Validated = "N/A";
    this->M2Garbled = "N/A";
    this->M2Derivation = "N/A";
    this->M2Code = "N/A";

}


void Cat20::FullDecode() {
    if (this->fspec.length() > 0) {

        if ((this->fspec.at(0) & 0x80) == 0x80) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeDataSourceIdentifier(dataItem);
        }
        if ((this->fspec.at(0) & 0x40) == 0x40) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetVariableLengthDataItem(this->data);
            this->DecodeTargetReportDescriptor(dataItem);
        }
        if ((this->fspec.at(0) & 0x20) == 0x20) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,3);
            this->DecodeTimeOfDay(dataItem);
        }
        if ((this->fspec.at(0) & 0x10) == 0x10) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,8);
            this->DecodePositionInWGS84Coordinates(dataItem);
        }
        if ((this->fspec.at(0) & 0x08) == 0x08) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,6);
            this->DecodePositionInCartesianCoordinates(dataItem);
        }
        if ((this->fspec.at(0) & 0x04) == 0x04) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeTrackNumber(dataItem);
        }
        if ((this->fspec.at(0) & 0x02) == 0x02) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetVariableLengthDataItem(this->data);
            this->DecodeTrackStatus(dataItem);
        }
    }
    if (this->fspec.length() > 1) {

        if ((this->fspec.at(1) & 0x80) == 0x80) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeMode3ACodeInOctalRepresentation(dataItem);
        }
        if ((this->fspec.at(1) & 0x40) == 0x40) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,4);
            this->DecodeCalculatedTrackVelocityInCartesianCoordinates(dataItem);
        }
        if ((this->fspec.at(1) & 0x20) == 0x20) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeFlightLevelInBinaryRepresentation(dataItem);
        }
        if ((this->fspec.at(1) & 0x10) == 0x10) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,4);
            this->DecodeModeCCode(dataItem);
        }
        if ((this->fspec.at(1) & 0x08) == 0x08) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,3);
            this->DecodeTargetAddress(dataItem);
        }
        if ((this->fspec.at(1) & 0x04) == 0x04) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,7);
            this->DecodeTargetIdentification(dataItem);
        }
        if ((this->fspec.at(1) & 0x02) == 0x02) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeMeasuredHeight(dataItem);
        }
    }
    if (this->fspec.length() > 2) {

        if ((this->fspec.at(2) & 0x80) == 0x80) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetRepetitiveDataItem(this->data,2);
            this->DecodeGeometricHeight(dataItem);
        }
        if ((this->fspec.at(2) & 0x40) == 0x40) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeCalculatedAcceleration(dataItem);
        }
        if ((this->fspec.at(2) & 0x20) == 0x20) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1);
            this->DecodeVehicleFleetIdentification(dataItem);
        }
        if ((this->fspec.at(2) & 0x10) == 0x10) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1);
            this->DecodePreProgrammedMessage(dataItem);
        }
        if ((this->fspec.at(2) & 0x08) == 0x08) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetVariableLengthDataItem(this->data);
            this->DecodePositionAccuracy(dataItem);
        }
        if ((this->fspec.at(2) & 0x04) == 0x04) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetRepetitiveDataItem(this->data,1);
            this->DecodeContributingDevices(dataItem);
        }
        if ((this->fspec.at(2) & 0x02) == 0x02) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetRepetitiveDataItem(this->data,8);
            this->DecodeBDSRegisterData(dataItem);
        }
    }
    if (this->fspec.length() > 3) {

        if ((this->fspec.at(3) & 0x80) == 0x80) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeCommsACASCapabilityAndFlightStatus(dataItem);
        }
        if ((this->fspec.at(3) & 0x40) == 0x40) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetRepetitiveDataItem(this->data,7);
            this->DecodeACASResolutionAdvisoryReport(dataItem);
        }
        if ((this->fspec.at(3) & 0x20) == 0x20) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetVariableLengthDataItem(this->data);
            this->DecodeWarningErrorConditions(dataItem);
        }
        if ((this->fspec.at(3) & 0x10) == 0x10) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1);
            this->DecodeMode1CodeInOctalRepresentation(dataItem);
        }
        if ((this->fspec.at(3) & 0x08) == 0x08) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeMode2CodeInOctalRepresentation(dataItem);
        }
        if ((this->fspec.at(3) & 0x04) == 0x04) {
            //this->DecodeSpecialPurposeField(dataItem);
        }
        if ((this->fspec.at(3) & 0x02) == 0x02) {
            //Reserved Expansion Field
        }
    }
}


void Cat20::DecodeDataSourceIdentifier(QVector<unsigned char> &dataItem) {}
void Cat20::DecodeTargetReportDescriptor(QVector<unsigned char> &dataItem) {}
void Cat20::DecodeTimeOfDay(QVector<unsigned char> &dataItem) {}
void Cat20::DecodePositionInWGS84Coordinates(QVector<unsigned char> &dataItem) {}
void Cat20::DecodePositionInCartesianCoordinates(QVector<unsigned char> &dataItem) {}
void Cat20::DecodeTrackNumber(QVector<unsigned char> &dataItem) {}
void Cat20::DecodeTrackStatus(QVector<unsigned char> &dataItem) {}
void Cat20::DecodeMode3ACodeInOctalRepresentation(QVector<unsigned char> &dataItem) {}
void Cat20::DecodeCalculatedTrackVelocityInCartesianCoordinates(QVector<unsigned char> &dataItem) {}
void Cat20::DecodeFlightLevelInBinaryRepresentation(QVector<unsigned char> &dataItem) {}
void Cat20::DecodeModeCCode(QVector<unsigned char> &dataItem) {}
void Cat20::DecodeTargetAddress(QVector<unsigned char> &dataItem) {}
void Cat20::DecodeTargetIdentification(QVector<unsigned char> &dataItem) {}
void Cat20::DecodeMeasuredHeight(QVector<unsigned char> &dataItem) {}
void Cat20::DecodeGeometricHeight(QVector<unsigned char> &dataItem) {}
void Cat20::DecodeCalculatedAcceleration(QVector<unsigned char> &dataItem) {}
void Cat20::DecodeVehicleFleetIdentification(QVector<unsigned char> &dataItem) {}
void Cat20::DecodePreProgrammedMessage(QVector<unsigned char> &dataItem) {}
void Cat20::DecodePositionAccuracy(QVector<unsigned char> &dataItem) {}
void Cat20::DecodeContributingDevices(QVector<unsigned char> &dataItem) {}
void Cat20::DecodeBDSRegisterData(QVector<unsigned char> &dataItem) {}
void Cat20::DecodeCommsACASCapabilityAndFlightStatus(QVector<unsigned char> &dataItem) {}
void Cat20::DecodeACASResolutionAdvisoryReport(QVector<unsigned char> &dataItem) {}
void Cat20::DecodeWarningErrorConditions(QVector<unsigned char> &dataItem) {}
void Cat20::DecodeMode1CodeInOctalRepresentation(QVector<unsigned char> &dataItem) {}
void Cat20::DecodeMode2CodeInOctalRepresentation(QVector<unsigned char> &dataItem) {}
