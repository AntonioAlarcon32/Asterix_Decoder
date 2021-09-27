#include "hdr/asterix_lib/cat10.h"
#include "hdr/asterix_lib/utilities.h"


Cat10::Cat10()
{
    this->category = 10;
    this->length = 0;
    this->systemAreaCode = 0;
    this->systemIdentificationCode = 0;
}

void Cat10::FullDecode() {

    if (this->fspec.length() > 0) {

        if ((this->fspec.at(0) & 0x80) == 0x80) {
            QVector<char> data = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeDataSourceIdentifier(data);
        }
        if ((this->fspec.at(0) & 0x40) == 0x40) {
            //this->DecodeMessageType(dataItem);
        }
        if ((this->fspec.at(0) & 0x20) == 0x20) {
            //this->DecodeTargetReportDescriptor(dataItem);
        }
        if ((this->fspec.at(0) & 0x10) == 0x10) {
            //this->DecodeTimeOfDay(dataItem);
        }
        if ((this->fspec.at(0) & 0x08) == 0x08) {
            //this->DecodePositionInWGS84Coordinates(dataItem);
        }
        if ((this->fspec.at(0) & 0x04) == 0x04) {
            //this->DecodeMeasuredPositionInPolarCoordinates(dataItem);
        }
        if ((this->fspec.at(0) & 0x02) == 0x02) {
            //this->DecodePositionInCartesianCoordinates(dataItem);
        }
    }

    if (this->fspec.length() > 1) {

        if ((this->fspec.at(1) & 0x80) == 0x80) {
            //this->DecodeCalculatedTrackVelocityInPolarCoordinates(dataItem);
        }
        if ((this->fspec.at(1) & 0x40) == 0x40) {
            //this->DecodeCalculatedTrackVelocityInCartesianCoordinates(dataItem);
        }
        if ((this->fspec.at(1) & 0x20) == 0x20) {
            //this->DecodeTrackNumber(dataItem);
        }
        if ((this->fspec.at(1) & 0x10) == 0x10) {
            //this->DecodeTrackStatus(dataItem);
        }
        if ((this->fspec.at(1) & 0x08) == 0x08) {
            //this->DecodeMode3ACodeInOctalRepresentation(dataItem);
        }
        if ((this->fspec.at(1) & 0x04) == 0x04) {
            //this->DecodeTargetAddress(dataItem);
        }
        if ((this->fspec.at(1) & 0x02) == 0x02) {
            //this->DecodeTargetIdentification(dataItem);
        }
    }
    if (this->fspec.length() > 2) {

        if ((this->fspec.at(2) & 0x80) == 0x80) {
            //this->DecodeModeSMBData(dataItem);
        }
        if ((this->fspec.at(2) & 0x40) == 0x40) {
            //this->DecodeVehicleFleetIdentification(dataItem);
        }
        if ((this->fspec.at(2) & 0x20) == 0x20) {
            //this->DecodeFlightLevelInBinaryRepresentation(dataItem);
        }
        if ((this->fspec.at(2) & 0x10) == 0x10) {
            //this->DecodeMeasuredHeight(dataItem);
        }
        if ((this->fspec.at(2) & 0x08) == 0x08) {
            //this->DecodeTargetSizeAndOrientation(dataItem);
        }
        if ((this->fspec.at(2) & 0x04) == 0x04) {
            //this->DecodeSystemStatus(dataItem);
        }
        if ((this->fspec.at(2) & 0x02) == 0x02) {
            //this->DecodePreProgrammedMessage(dataItem);
        }
    }
    if (this->fspec.length() > 3) {

        if ((this->fspec.at(3) & 0x80) == 0x80) {
            //this->DecodeStandardDeviationOfPosition(dataItem);
        }
        if ((this->fspec.at(3) & 0x40) == 0x40) {
            //this->DecodePresence(dataItem);
        }
        if ((this->fspec.at(3) & 0x20) == 0x20) {
            //this->DecodeAmplitudeOfPrimaryPlot(dataItem);
        }
        if ((this->fspec.at(3) & 0x10) == 0x10) {
            //this->DecodeCalculatedAcceleration(dataItem);
        }
        if ((this->fspec.at(3) & 0x08) == 0x08) {
            //Spare
        }
        if ((this->fspec.at(3) & 0x04) == 0x04) {
            //this->DecodeSpecialPurposeField(dataItem);
        }
        if ((this->fspec.at(2) & 0x02) == 0x02) {
            //Reserved Expansion Field
        }
    }
}

void Cat10::DecodeDataSourceIdentifier(QVector<char> &dataItem) {
    this->systemAreaCode = (short)dataItem.at(0);
    this->systemIdentificationCode = (short)dataItem.at(1);

}
