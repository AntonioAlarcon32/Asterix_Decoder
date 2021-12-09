#include "hdr/asterix_lib/cat19.h"

Cat19::Cat19()
{
    this->category = 19;
    this->length = 0;
    this->offset = 0;

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
    this->wgs84undulation = -128;
}


QString Cat19::GetTypeOfMessage() {
    return this->typeOfMessage;
}

QTime Cat19::GetTimeOfReception() {
    return this->timeOfDay;
}

QString Cat19::GetSACSIC() {
    AppConfig *conf = AppConfig::GetInstance();
    Sensor sensor = conf->GetSensorFromSACSIC(systemAreaCode,systemIdentificationCode);
    if (sensor.systemAreaCode == systemAreaCode && sensor.systemIdCode == systemIdentificationCode) {
        return sensor.sensorDescription;
    }
    else {
        return QString::number(systemAreaCode) + "/" + QString::number(systemIdentificationCode);
    }

}


WGS84Coordinates Cat19::GetPosition() {
    return WGS84Coordinates(0,0,0);
}

QString Cat19::GetIdentifier() {
    return "N/A";
}

QString Cat19::GetCallSign() {
    return "N/A";
}
QString Cat19::GetAddress() {
    return "N/A";
}
QString Cat19::GetTrackNumber() {
    return "N/A";
}

QTreeWidgetItem* Cat19::GetPacketInfo() {
    QTreeWidgetItem *root = new QTreeWidgetItem();
    root->setText(0, "Packet " + QString::number(this->numOfPacket));

    QTreeWidgetItem *cat = new QTreeWidgetItem();
    cat->setText(0, "Category");
    cat->setText(1,QString::number(this->category));
    root->addChild(cat);

    QTreeWidgetItem *len = new QTreeWidgetItem();
    len->setText(0, "Length");
    len->setText(1,QString::number(this->length));
    root->addChild(len);

    QTreeWidgetItem *dataItems = new QTreeWidgetItem();
    dataItems->setText(0, "Data Items");
    root->addChild(dataItems);

    QTreeWidgetItem *messageType = new QTreeWidgetItem();
    messageType->setText(0,"I019/000, Message Type");
    dataItems->addChild(messageType);
    QTreeWidgetItem *mt = new QTreeWidgetItem();
    mt->setText(0,"Message Type");
    mt->setText(1,this->typeOfMessage);
    messageType->addChild(mt);


    QTreeWidgetItem *dataSourceId = new QTreeWidgetItem();
    dataSourceId->setText(0, "I019/010, Data Source Identifier");
    dataItems->addChild(dataSourceId);
    QTreeWidgetItem *systemAreaCode = new QTreeWidgetItem();
    systemAreaCode->setText(0,"System Area Code");
    systemAreaCode->setText(1,QString::number(this->systemAreaCode));
    dataSourceId->addChild(systemAreaCode);
    QTreeWidgetItem *systemIdCode = new QTreeWidgetItem();
    systemIdCode->setText(0,"System Identification Code");
    systemIdCode->setText(1,QString::number(this->systemIdentificationCode));
    dataSourceId->addChild(systemIdCode);

    if (this->timeOfDay != QTime()) {
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I019/140, Time of Day");
        dataItems->addChild(child);
        QTreeWidgetItem *v = new QTreeWidgetItem();
        v->setText(0,"Time Of Day");
        v->setText(1,this->timeOfDay.toString("hh:mm:ss:zzz"));
        child->addChild(v);
    }

    if (this->ssNogo != "N/A") {
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I019/550, System Status");
        dataItems->addChild(child);
        QTreeWidgetItem *v = new QTreeWidgetItem();
        v->setText(0,"NOGO");
        v->setText(1,this->ssNogo);
        child->addChild(v);
        QTreeWidgetItem *v2 = new QTreeWidgetItem();
        v2->setText(0,"OVL");
        v2->setText(1,this->ssOvl);
        child->addChild(v2);
        QTreeWidgetItem *v3 = new QTreeWidgetItem();
        v3->setText(0,"TSV");
        v3->setText(1,this->ssTsv);
        child->addChild(v3);
        QTreeWidgetItem *v5 = new QTreeWidgetItem();
        v5->setText(0,"TTF");
        v5->setText(1,this->ssTtf);
        child->addChild(v5);
    }

    if (this->tp1Status != "N/A") {

        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I019/551, Tracking Processor Detailed Status");
        dataItems->addChild(child);
        if (this->tp1Status != "N/A") {
            QTreeWidgetItem *v = new QTreeWidgetItem();
            v->setText(0,"Tracking Processor 1 Status");
            v->setText(1,this->tp1Status);
            child->addChild(v);
        }

        if (this->tp2Status != "N/A") {
            QTreeWidgetItem *v = new QTreeWidgetItem();
            v->setText(0,"Tracking Processor 2 Status");
            v->setText(1,this->tp2Status);
            child->addChild(v);
        }

        if (this->tp3Status != "N/A") {
            QTreeWidgetItem *v = new QTreeWidgetItem();
            v->setText(0,"Tracking Processor 3 Status");
            v->setText(1,this->tp3Status);
            child->addChild(v);
        }

        if (this->tp4Status != "N/A") {
            QTreeWidgetItem *v = new QTreeWidgetItem();
            v->setText(0,"Tracking Processor 4 Status");
            v->setText(1,this->tp4Status);
            child->addChild(v);
        }
    }

    if (this->rt1Status != "N/A") {
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I019/553, Reference Transponder Detailed Status");
        dataItems->addChild(child);
        if (this->rt1Status != "N/A") {
            QTreeWidgetItem *v = new QTreeWidgetItem();
            v->setText(0,"Reference Transponder 1 Status");
            v->setText(1,this->rt1Status);
            child->addChild(v);
        }

        if (this->rt1Status != "N/A") {
            QTreeWidgetItem *v = new QTreeWidgetItem();
            v->setText(0,"Reference Transponder 2 Status");
            v->setText(1,this->rt2Status);
            child->addChild(v);
        }

        if (this->rt1Status != "N/A") {
            QTreeWidgetItem *v = new QTreeWidgetItem();
            v->setText(0,"Reference Transponder 3 Status");
            v->setText(1,this->rt3Status);
            child->addChild(v);
        }

        if (this->rt1Status != "N/A") {
            QTreeWidgetItem *v = new QTreeWidgetItem();
            v->setText(0,"Reference Transponder 4 Status");
            v->setText(1,this->rt4Status);
            child->addChild(v);
        }
    }

    if (!isnan(this->wgs84latitude)) {
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I019/600, Position of the MLT System Reference Point");
        dataItems->addChild(child);
        QTreeWidgetItem *lat = new QTreeWidgetItem();
        QTreeWidgetItem *lon = new QTreeWidgetItem();
        lat->setText(0,"Latitude [º]");
        lat->setText(1,QString::number(this->wgs84latitude));
        child->addChild(lat);
        lon->setText(0,"Longitude [º]");
        lon->setText(1,QString::number(this->wgs84longitude));
        child->addChild(lon);
    }

    if (!isnan(this->wgs84height)) {
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I019/610, Height of the MLT System Reference Point");
        dataItems->addChild(child);
        QTreeWidgetItem *v = new QTreeWidgetItem();
        v->setText(0,"Height of the MLT Reference Point [m]");
        v->setText(1,QString::number(this->wgs84height));
        child->addChild(v);
    }

    if (this->wgs84undulation != -128) {
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I019/620, WGS-84 Undulation");
        dataItems->addChild(child);
        QTreeWidgetItem *v = new QTreeWidgetItem();
        v->setText(0,"WGS84 undulation [m]");
        v->setText(1,QString::number(this->wgs84undulation));
        child->addChild(v);
    }

    return root;

}




void Cat19::FullDecode() {
    if (this->fspec.length() > 0) {

        if ((this->fspec.at(0) & 0x80) == 0x80) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2,this->offset);
            this->DecodeDataSourceIdentifier(dataItem);
        }
        if ((this->fspec.at(0) & 0x40) == 0x40) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1,this->offset);
            this->DecodeMessageType(dataItem);
        }
        if ((this->fspec.at(0) & 0x20) == 0x20) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,3,this->offset);
            this->DecodeTimeOfDay(dataItem);
        }
        if ((this->fspec.at(0) & 0x10) == 0x10) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1,this->offset);
            this->DecodeSystemStatus(dataItem);
        }
        if ((this->fspec.at(0) & 0x08) == 0x08) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1,this->offset);
            this->DecodeTrackingProcessorDetailedStatus(dataItem);
        }
        if ((this->fspec.at(0) & 0x04) == 0x04) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetRepetitiveDataItem(this->data,2,this->offset);
            this->DecodeRemoteSensorDetailedStatus(dataItem);
        }
        if ((this->fspec.at(0) & 0x02) == 0x02) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetVariableLengthDataItem(this->data,this->offset);
            this->DecodeReferenceTrasponderDetailedStatus(dataItem);
        }
    }

    if (this->fspec.length() > 1) {

        if ((this->fspec.at(1) & 0x80) == 0x80) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,8,this->offset);
            this->DecodePositionOfTheMLTSystemReferencePoint(dataItem);
        }
        if ((this->fspec.at(1) & 0x40) == 0x40) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2,this->offset);
            this->DecodeHeightOfTheMLTSystemReferencePoint(dataItem);
        }
        if ((this->fspec.at(1) & 0x20) == 0x20) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1,this->offset);
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

void Cat19::DecodeDataSourceIdentifier(QVector<unsigned char> &dataItem) {
    this->systemAreaCode = (short)dataItem.at(0);
    this->systemIdentificationCode = (short)dataItem.at(1);
}
void Cat19::DecodeMessageType(QVector<unsigned char> &dataItem) {
    switch (dataItem.at(0)) {
    case 0x01:
        this->typeOfMessage = "Start of Update Cycle";
        break;
    case 0x02:
        this->typeOfMessage = "Periodic Status Message";
        break;
    case 0x03:
        this->typeOfMessage = "Event-triggered Status Message";
        break;
    }
}

void Cat19::DecodeTimeOfDay(QVector<unsigned char> &dataItem) {
    double timeResolution = pow(2,-7);
    double seconds = Utilities::DataTools::DecodeUnsignedBytesToDouble(dataItem,timeResolution);
    int mseconds = seconds * 1000;
    this->timeOfDay = QTime::fromMSecsSinceStartOfDay(mseconds);
}

void Cat19::DecodeSystemStatus(QVector<unsigned char> &dataItem) {

    unsigned char nogoMask = 0b11000000;
    unsigned char ovlMask = 0b00100000;
    unsigned char tsvMask = 0b00010000;
    unsigned char ttfMask = 0b00001000;

    unsigned char nogo = (dataItem.at(0) & nogoMask) >> 6;
    unsigned char ovl = (dataItem.at(0) & ovlMask) >> 5;
    unsigned char tsv = (dataItem.at(0) & tsvMask) >> 4;
    unsigned char ttf = (dataItem.at(0) & ttfMask) >> 3;

    switch (nogo) {
    case 0:
        this->ssNogo = "Operational";
        break;
    case 1:
        this->ssNogo = "Degraded";
        break;
    case 2:
        this->ssNogo = "NOGO";
        break;
    case 3:
        this->ssNogo = "undefined";
        break;
    }

    switch (ovl) {
    case 0:
        this->ssOvl = "No overload";
        break;
    case 1:
        this->ssOvl = "Overload";
        break;

    }

    switch (tsv) {
    case 0:
        this->ssTsv = "Valid";
        break;
    case 1:
        this->ssTsv = "Invalid";
        break;
    }

    switch (ttf) {
    case 0:
        this->ssTtf = "Test Target Operative";
        break;
    case 1:
        this->ssTtf = "Test Target Failure";
        break;
    }
}

void Cat19::DecodeTrackingProcessorDetailedStatus(QVector<unsigned char> &dataItem) {

    unsigned char tp1Mask = 0b11000000;
    unsigned char tp2Mask = 0b00110000;
    unsigned char tp3Mask = 0b00001100;
    unsigned char tp4Mask = 0b00000011;

    unsigned char tp1 = (dataItem.at(0) & tp1Mask) >> 6;
    unsigned char tp2 = (dataItem.at(0) & tp2Mask) >> 4;
    unsigned char tp3 = (dataItem.at(0) & tp3Mask) >> 2;
    unsigned char tp4 = (dataItem.at(0) & tp4Mask) >> 3;

    switch (tp1) {
    case 0:
        this->tp1Status = "TP not used";
        break;
    case 1:
        this->tp1Status = "Standby/Good";
        break;
    case 2:
        this->tp1Status = "Exec/Faulted";
        break;
    case 3:
        this->tp1Status = "Exec/Standby";
        break;
    }

    switch (tp2) {
    case 0:
        this->tp2Status = "TP not used";
        break;
    case 1:
        this->tp2Status = "Standby/Good";
        break;
    case 2:
        this->tp2Status = "Exec/Faulted";
        break;
    case 3:
        this->tp2Status = "Exec/Standby";
        break;
    }

    switch (tp3) {
    case 0:
        this->tp3Status = "TP not used";
        break;
    case 1:
        this->tp3Status = "Standby/Good";
        break;
    case 2:
        this->tp3Status = "Exec/Faulted";
        break;
    case 3:
        this->tp3Status = "Exec/Standby";
        break;
    }

    switch (tp4) {
    case 0:
        this->tp4Status = "TP not used";
        break;
    case 1:
        this->tp4Status = "Standby/Good";
        break;
    case 2:
        this->tp4Status = "Exec/Faulted";
        break;
    case 3:
        this->tp4Status = "Exec/Standby";
        break;
    }
}
void Cat19::DecodeRemoteSensorDetailedStatus(QVector<unsigned char> &dataItem) {

    unsigned char repetitions = dataItem.first();
    dataItem.removeFirst();

    for (int c = 0; c < repetitions; c++) {

        this->rsIds.append(dataItem.at(0));
        dataItem.removeFirst();

        QString type = "";
        QString status = "";

        unsigned char r1090MHz = (dataItem.at(0) & 0b01000000) >> 6;
        unsigned char t1030MHz = (dataItem.at(0) & 0b00100000) >> 5;
        unsigned char t1090MHz = (dataItem.at(0) & 0b00010000) >> 4;

        unsigned char rsStatus = (dataItem.at(0) & 0b00001000) >> 3;
        unsigned char rsOperational = (dataItem.at(0) & 0b00000100) >> 2;

        if (r1090MHz == 1) {
            type.append("Receiver 1090MHz present,");
        }
        if (t1030MHz == 1) {
            type.append("Transmitter 1030MHz present,");
        }
        if (t1090MHz == 1) {
            type.append("Transmitter 1090MHz present,");
        }

        if (rsStatus == 1) {
            status.append("RS Status: Good,");
        }
        else if (rsStatus == 0) {
            status.append("RS Status: Faulted,");
        }

        if (rsOperational == 1) {
            status.append("RS Operational: Online,");
        }
        else if (rsOperational == 0) {
            status.append("RS Status: Offline,");
        }

        this->rsOperationals.append(status);
        this->rsTypes.append(type);
    }
}

void Cat19::DecodeReferenceTrasponderDetailedStatus(QVector<unsigned char> &dataItem) {
    unsigned char rf1Mask = 0b11000000;
    unsigned char rf2Mask = 0b00001100;

    unsigned char rf1 = (dataItem.at(0) & rf1Mask) >> 6;
    unsigned char rf2 = (dataItem.at(0) & rf2Mask) >> 2;

    switch (rf1) {
    case 0:
        this->rt1Status = "";
        break;
    case 1:
        this->rt1Status = "Warning";
        break;
    case 2:
        this->rt1Status = "Faulted";
        break;
    case 3:
        this->rt1Status = "Good";
        break;
    }

    switch (rf2) {
    case 0:
        this->rt2Status = "";
        break;
    case 1:
        this->rt2Status = "Warning";
        break;
    case 2:
        this->rt2Status = "Faulted";
        break;
    case 3:
        this->rt2Status = "Good";
        break;
    }

    if (dataItem.length() > 1) {
        unsigned char rf3 = (dataItem.at(0) & rf1Mask) >> 6;
        unsigned char rf4 = (dataItem.at(0) & rf2Mask) >> 2;

        switch (rf3) {
        case 0:
            this->rt3Status = "";
            break;
        case 1:
            this->rt3Status = "Warning";
            break;
        case 2:
            this->rt3Status = "Faulted";
            break;
        case 3:
            this->rt3Status = "Good";
            break;
        }

        switch (rf4) {
        case 0:
            this->rt4Status = "";
            break;
        case 1:
            this->rt4Status = "Warning";
            break;
        case 2:
            this->rt4Status = "Faulted";
            break;
        case 3:
            this->rt4Status = "Good";
            break;
        }
    }
}

void Cat19::DecodePositionOfTheMLTSystemReferencePoint(QVector<unsigned char> &dataItem) {

    QVector<unsigned char> latitudeBytes = {dataItem.at(0), dataItem.at(1), dataItem.at(2),dataItem.at(3)};
    QVector<unsigned char> longitudeBytes = {dataItem.at(4), dataItem.at(5), dataItem.at(6),dataItem.at(7)};
    double resolution = 180 / pow(2,30);
    this->wgs84latitude = Utilities::DataTools::DecodeTwosComplementToDouble(latitudeBytes, resolution);
    this->wgs84longitude = Utilities::DataTools::DecodeTwosComplementToDouble(longitudeBytes, resolution);
}

void Cat19::DecodeHeightOfTheMLTSystemReferencePoint(QVector<unsigned char> &dataItem) {

    double resolution = 0.25;
    this->wgs84height = Utilities::DataTools::DecodeTwosComplementToDouble(dataItem, resolution);

}

void Cat19::DecodeWGS84Undulation(QVector<unsigned char> &dataItem) {

    double resolution = 1;
    this->wgs84undulation = Utilities::DataTools::DecodeTwosComplementToDouble(dataItem, resolution);
}
