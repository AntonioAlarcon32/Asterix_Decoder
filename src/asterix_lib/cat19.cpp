#include "hdr/asterix_lib/cat19.h"

Cat19::Cat19()
{
    this->category = 19;
    this->length = 0;

    this->systemAreaCode = 0;
    this->systemIdentificationCode = 0;

    this->typeOfMessage = "N/A";

    this->timeOfDay = QTime();

    this->ssNogo = "N/A";
    this->ssOvl = "N/A";
    this->ssTsv = "N/A";
    this->ssTtf = "N/A";

    this->tp1Status = "N/A";
    this->tp2Status = "N/A";
    this->tp3Status = "N/A";
    this->tp4Status = "N/A";

    this->rt1Status = "N/A";
    this->rt2Status = "N/A";
    this->rt3Status = "N/A";
    this->rt4Status = "N/A";

    this->wgs84latitude = nan("");
    this->wgs84longitude = nan("");

    this->wgs84height = nan("");
    this->wgs84undulation = 0;
}

void Cat19::FullDecode() {
    if (this->fspec.length() > 0) {

        if ((this->fspec.at(0) & 0x80) == 0x80) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeDataSourceIdentifier(dataItem);
        }
        if ((this->fspec.at(0) & 0x40) == 0x40) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1);
            this->DecodeMessageType(dataItem);
        }
        if ((this->fspec.at(0) & 0x20) == 0x20) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,3);
            this->DecodeTimeOfDay(dataItem);
        }
        if ((this->fspec.at(0) & 0x10) == 0x10) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1);
            this->DecodeSystemStatus(dataItem);
        }
        if ((this->fspec.at(0) & 0x08) == 0x08) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1);
            this->DecodeTrackingProcessorDetailedStatus(dataItem);
        }
        if ((this->fspec.at(0) & 0x04) == 0x04) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetRepetitiveDataItem(this->data,2);
            this->DecodeRemoteSensorDetailedStatus(dataItem);
        }
        if ((this->fspec.at(0) & 0x02) == 0x02) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetVariableLengthDataItem(this->data);
            this->DecodeReferenceTrasponderDetailedStatus(dataItem);
        }
    }

    if (this->fspec.length() > 1) {

        if ((this->fspec.at(1) & 0x80) == 0x80) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,8);
            this->DecodePositionOfTheMLTSystemReferencePoint(dataItem);
        }
        if ((this->fspec.at(1) & 0x40) == 0x40) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeHeightOfTheMLTSystemReferencePoint(dataItem);
        }
        if ((this->fspec.at(1) & 0x20) == 0x20) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1);
            this->DecodeWGS84Undulation(dataItem);
        }
        if ((this->fspec.at(1) & 0x10) == 0x10) {
            //SPARE
        }
        if ((this->fspec.at(1) & 0x08) == 0x08) {
            //SPARE
        }
        if ((this->fspec.at(1) & 0x04) == 0x04) {
            //RESERVED EXPANSION FIELD
        }
        if ((this->fspec.at(1) & 0x02) == 0x02) {
            //SPECIAL PURPOSE FIELD
        }
    }
}

void Cat19::DecodeDataSourceIdentifier(QVector<unsigned char> &dataItem) {}
void Cat19::DecodeMessageType(QVector<unsigned char> &dataItem) {}
void Cat19::DecodeTimeOfDay(QVector<unsigned char> &dataItem) {}
void Cat19::DecodeSystemStatus(QVector<unsigned char> &dataItem) {}
void Cat19::DecodeTrackingProcessorDetailedStatus(QVector<unsigned char> &dataItem) {}
void Cat19::DecodeRemoteSensorDetailedStatus(QVector<unsigned char> &dataItem) {}
void Cat19::DecodeReferenceTrasponderDetailedStatus(QVector<unsigned char> &dataItem) {}
void Cat19::DecodePositionOfTheMLTSystemReferencePoint(QVector<unsigned char> &dataItem) {}
void Cat19::DecodeHeightOfTheMLTSystemReferencePoint(QVector<unsigned char> &dataItem) {}
void Cat19::DecodeWGS84Undulation(QVector<unsigned char> &dataItem) {}
