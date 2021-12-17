#include <hdr/asterix_lib/asterixfile.h>



AsterixFile::AsterixFile()
{
    dataBlocks = new QVector<DataBlock*>();
    packetTable_ = new QStandardItemModel;
    emitterTable_ = new QStandardItemModel;
    emitters_ = QList<Emitter>();
    fileInfo_ = QFileInfo();
    categoryStats_ = QMap<int,int>();
    filteredPackets_ = QList<int>();
    numberOfPackets_ = 0;
}

AsterixFile::~AsterixFile() {
    delete dataBlocks;
    delete packetTable_;
}

void AsterixFile::readFile(QString path) {

    dataBlocks->clear();
    packetTable_->clear();

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        return;
    fileInfo_ = QFileInfo(file);
    QByteArray fileBinary = file.readAll();
    int numOfPackets = 0;
    QElapsedTimer* testTime = new QElapsedTimer();
    testTime->start();
    int offset;
    bool packetDecoded = false;
    if (fileInfo_.completeSuffix() == "ast") {
        offset = 0;
    }
    else if (fileInfo_.completeSuffix() == "gps") {
        offset = 2200;
    }
    else {
        return;
    }

    for (; offset < fileBinary.length(); ) {


        int category = fileBinary[offset];
        int length =  fileBinary[offset + 2] << fileBinary[offset + 1] ;
        packetDecoded = false;

        try {

            if (category == 10) {

                Cat10 *cat10Block = new Cat10();
                cat10Block->SetLength(length);
                QByteArray data = fileBinary.mid(offset,length);
                cat10Block->SetData(data);
                cat10Block->offset = 3;
                cat10Block->DecodeFSPEC();
                cat10Block->FullDecode();
                dataBlocks->append(cat10Block);
            }

            else if (category == 19) {
                Cat19 *cat19Block = new Cat19();
                cat19Block->SetLength(length);
                QByteArray data = fileBinary.mid(offset,length);
                cat19Block->SetData(data);
                cat19Block->offset = 3;
                cat19Block->DecodeFSPEC();
                cat19Block->FullDecode();
                dataBlocks->append(cat19Block);

            }

            else if (category == 20) {
                Cat20 *cat20Block = new Cat20();
                cat20Block->SetLength(length);
                QByteArray data = fileBinary.mid(offset,length);
                cat20Block->SetData(data);
                cat20Block->offset = 3;
                cat20Block->DecodeFSPEC();
                cat20Block->FullDecode();
                dataBlocks->append(cat20Block);

            }

            else if (category == 21) {
                Cat21 *cat21Block = new Cat21();
                cat21Block->SetLength(length);
                QByteArray data = fileBinary.mid(offset,length);
                cat21Block->SetData(data);
                cat21Block->offset = 3;
                cat21Block->DecodeFSPEC();
                cat21Block->FullDecode();
                dataBlocks->append(cat21Block);
            }

            else {

                OtherDataBlocks *other = new OtherDataBlocks(category);
                other->SetLength(length);
                QByteArray data = fileBinary.mid(offset,length);
                other->SetData(data);
                other->offset = 3;
                dataBlocks->append(other);
            }
            packetDecoded = true;


        }  catch (...) {

            packetDecoded = false;
            qDebug() << "ERROR IN PACKET" << numOfPackets + 1;

        }

        //Cat10 *inten = static_cast<Cat10*>(dataBlocks->at(0));
        //Cat10 *inten2 = dynamic_cast<Cat10*>(dataBlocks->at(0));
        if (packetDecoded == true) {
            numOfPackets++;
            filteredPackets_.append(numOfPackets);

            if (categoryStats_.value(category,0) == 0) {
                categoryStats_.insert(category,1);
            }
            else {
                categoryStats_[category]++;
            }

            dataBlocks->at(numOfPackets-1)->SetNumOfPacket(numOfPackets);

            QString typeOfMessage = dataBlocks->last()->GetTypeOfMessage();
            QTime timeOfReception = dataBlocks->last()->GetTimeOfReception();
            QString sicsac = dataBlocks->last()->GetSACSIC();
            QString timeToShow = "N/A";

            if (!timeOfReception.isNull()) {
                timeToShow = timeOfReception.toString("hh:mm:ss:zzz");
            }

            if ((numOfPackets % 1000) == 0) {
                emit packetLoaded();
            }
            packetTable_->appendRow({new QStandardItem(QString::number(numOfPackets)),new QStandardItem(QString::number(category)),
                                     new QStandardItem(QString::number(length)),new QStandardItem(sicsac),
                                     new QStandardItem(timeToShow),new QStandardItem(typeOfMessage)});
        }
        offset += length;
        if (fileInfo_.completeSuffix() == "gps") {
            offset += 10;
        }
    }
    packetTable_->setHorizontalHeaderLabels({"Packet","Category", "Length", "SAC/SIC", "Time of Transmission", "Type of Message"});

    this->ProcessEmitters();

    emit finishLoading();
     qDebug() << "Loading took" << testTime->elapsed() << "milliseconds";
     qDebug() << "Loaded " << numOfPackets << " packets";
     this->numberOfPackets_ = numOfPackets;
}

int AsterixFile::GetTotalPackets(QString path) {

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        return 0;
    QFileInfo fileInfo = QFileInfo(file);
    QByteArray fileBinary = file.readAll();
    int numOfPackets = 0;
    QElapsedTimer* testTime = new QElapsedTimer();
    testTime->start();
    int offset;
    if (fileInfo.completeSuffix() == "ast") {
        offset = 0;
    }
    else if (fileInfo.completeSuffix() == "gps") {
        offset = 2200;
    }
    else {
        return 0;
    }

    for (; offset < fileBinary.length(); ) {
        int length =  fileBinary[offset + 2] << fileBinary[offset + 1];
        numOfPackets++;
        offset += length;
        if (fileInfo.completeSuffix() == "gps") {
            offset += 10;
        }
    }
    return numOfPackets;
}

void AsterixFile::ProcessEmitters() {

    QList<QString> identifiers = QList<QString>();
    int i = 0;

    for (DataBlock *dataBlock : *dataBlocks) {

        if (dataBlock->GetIdentifier() != "N/A") {
            int index = identifiers.indexOf(dataBlock->GetIdentifier());
            i++;

            if (index == -1) {
                Emitter newEmitter = Emitter(dataBlock->GetIdentifier());
                newEmitter.AddPoint(dataBlock->GetPosition(), dataBlock->GetTimeOfReception(), dataBlock->category);
                identifiers.append(dataBlock->GetIdentifier());
                emitters_.append(newEmitter);
            }
                else {
                emitters_[index].AddPoint(dataBlock->GetPosition(), dataBlock->GetTimeOfReception(), dataBlock->category);
            }

        }
    }
    for (Emitter emitter: emitters_) {
        emitterTable_->appendRow({new QStandardItem(emitter.GetIdentifier()),
                                  new QStandardItem(emitter.GetFirstReport().toString("hh:mm:ss:zzz")),
                                  new QStandardItem(emitter.GetLastReport().toString("hh:mm:ss:zzz"))});
    }
    emitterTable_->setHorizontalHeaderLabels({"CallSign", "First Report at", "Last Report At"});
}

void AsterixFile::FilterByCallSign(QString callSign, QList<int> &packetList) {
    int i = 0;
    while (i < packetList.length()) {
        int numOfPacket = packetList.at(i);
        DataBlock* dataBlock = dataBlocks->at(numOfPacket-1);
        if (dataBlock->GetCallSign().replace(" ","") == callSign) {
            i++;
        }
        else {
            packetList.removeAt(i);
        }

    }
}

void AsterixFile::FilterByCategory(int category, QList<int> &packetList) {
    int i = 0;
    while (i < packetList.length()) {
        int numOfPacket = packetList.at(i);
        DataBlock* dataBlock = dataBlocks->at(numOfPacket-1);
        if (dataBlock->GetCategory() == category) {
            i++;
        }
        else {
            packetList.removeAt(i);
        }

    }
}

void AsterixFile::FilterByAddress(QString address, QList<int> &packetList) {
    int i = 0;
    while (i < packetList.length()) {
        int numOfPacket = packetList.at(i);
        DataBlock* dataBlock = dataBlocks->at(numOfPacket-1);
        if (dataBlock->GetAddress().replace(" ","") == address) {
            i++;
        }
        else {
            packetList.removeAt(i);
        }

    }
}

void AsterixFile::FilterByTrackNumber(int trackNumber, QList<int> &packetList) {
    int i = 0;
    while (i < packetList.length()) {
        int numOfPacket = packetList.at(i);
        DataBlock* dataBlock = dataBlocks->at(numOfPacket-1);
        if (dataBlock->GetTrackNumber() == trackNumber) {
            i++;
        }
        else {
            packetList.removeAt(i);
        }

    }
}

void AsterixFile::FilterByMode3A(int mode3ACode, QList<int> &packetList) {
    int i = 0;
    while (i < packetList.length()) {
        int numOfPacket = packetList.at(i);
        DataBlock* dataBlock = dataBlocks->at(numOfPacket-1);
        if (dataBlock->GetMode3A().toInt() == mode3ACode) {
            i++;
        }
        else {
            packetList.removeAt(i);
        }

    }
}

void AsterixFile::ApplyFilters(int category, QString callSign, QString address, int trackNumber, int mode3ACode) {

    if (category != -1) {
        this->FilterByCategory(category,this->filteredPackets_);
    }

    if (callSign != "") {
        this->FilterByCallSign(callSign,this->filteredPackets_);
    }

    if (address != "") {
        this->FilterByAddress(address,this->filteredPackets_);
    }

    if (trackNumber != -1) {
        this->FilterByTrackNumber(trackNumber,this->filteredPackets_);
    }

    if (mode3ACode != -1) {
        this->FilterByMode3A(mode3ACode,this->filteredPackets_);
    }

    packetTable_->clear();

    for (int i : this->filteredPackets_) {

        DataBlock* dataBlock = this->dataBlocks->at(i-1);

        QString typeOfMessage = dataBlock->GetTypeOfMessage();
        QTime timeOfReception = dataBlock->GetTimeOfReception();
        QString sicsac = dataBlock->GetSACSIC();
        QString timeToShow = "N/A";
        int category = dataBlock->GetCategory();
        int packetNumber = dataBlock->GetNumOfPacket();
        int length = dataBlock->GetLength();

        if (!timeOfReception.isNull()) {
            timeToShow = timeOfReception.toString("hh:mm:ss:zzz");
        }

        packetTable_->appendRow({new QStandardItem(QString::number(packetNumber)),new QStandardItem(QString::number(category)),
                                 new QStandardItem(QString::number(length)),new QStandardItem(sicsac),
                                 new QStandardItem(timeToShow),new QStandardItem(typeOfMessage)});
    }
    packetTable_->setHorizontalHeaderLabels({"Packet","Category", "Length", "SAC/SIC", "Time of Transmission", "Type of Message"});
}

void AsterixFile::ResetFilters() {
    filteredPackets_.clear();
    packetTable_->clear();
    for (DataBlock *dataBlock : *dataBlocks) {
        QString typeOfMessage = dataBlock->GetTypeOfMessage();
        QTime timeOfReception = dataBlock->GetTimeOfReception();
        QString sicsac = dataBlock->GetSACSIC();
        QString timeToShow = "N/A";
        int category = dataBlock->GetCategory();
        int packetNumber = dataBlock->GetNumOfPacket();
        int length = dataBlock->GetLength();
        filteredPackets_.append(dataBlock->GetNumOfPacket());

        if (!timeOfReception.isNull()) {
            timeToShow = timeOfReception.toString("hh:mm:ss:zzz");
        }

        packetTable_->appendRow({new QStandardItem(QString::number(packetNumber)),new QStandardItem(QString::number(category)),
                                 new QStandardItem(QString::number(length)),new QStandardItem(sicsac),
                                 new QStandardItem(timeToShow),new QStandardItem(typeOfMessage)});
    }
    packetTable_->setHorizontalHeaderLabels({"Packet","Category", "Length", "SAC/SIC", "Time of Transmission", "Type of Message"});
}

void AsterixFile::writeFile(QString filePath) {
    QFile file(filePath);
    if (!file.open(QFile::WriteOnly)) {
        qDebug() << "Could not open file for writing";
        return;
    }

    if (this->filteredPackets_.length() != 0) {
        for (int i : this->filteredPackets_) {
            DataBlock* dataBlock = dataBlocks->at(i-1);
            file.write(dataBlock->GetData());
        }
    }

    else {
        for (DataBlock* dataBlock : *this->dataBlocks) {
            file.write(dataBlock->GetData());
        }
    }
}

bool AsterixFile::AddPacketToList(QByteArray data) {

    int category = data.at(0);
    int length =  data.at(2) << data.at(1) ;
    bool packetDecoded = false;

    try {

        if (category == 10) {
            Cat10 *cat10Block = new Cat10();
            cat10Block->SetLength(length);
            cat10Block->SetData(data);
            cat10Block->offset = 3;
            cat10Block->DecodeFSPEC();
            cat10Block->FullDecode();
            dataBlocks->append(cat10Block);
        }

        else if (category == 19) {
            Cat19 *cat19Block = new Cat19();
            cat19Block->SetLength(length);
            cat19Block->SetData(data);
            cat19Block->offset = 3;
            cat19Block->DecodeFSPEC();
            cat19Block->FullDecode();
            dataBlocks->append(cat19Block);

        }

        else if (category == 20) {
            Cat20 *cat20Block = new Cat20();
            cat20Block->SetLength(length);
            cat20Block->SetData(data);
            cat20Block->offset = 3;
            cat20Block->DecodeFSPEC();
            cat20Block->FullDecode();
            dataBlocks->append(cat20Block);

        }

        else if (category == 21) {
            Cat21 *cat21Block = new Cat21();
            cat21Block->SetLength(length);
            cat21Block->SetData(data);
            cat21Block->offset = 3;
            cat21Block->DecodeFSPEC();
            cat21Block->FullDecode();
            dataBlocks->append(cat21Block);
        }

        else {
            OtherDataBlocks *other = new OtherDataBlocks(category);
            other->SetLength(length);
            other->SetData(data);
            other->offset = 3;
            dataBlocks->append(other);
        }
        packetDecoded = true;
    }  catch (...) {
        packetDecoded = false;
        qDebug() << "ERROR IN PACKET";

    }

    if (packetDecoded == true) {

        numberOfPackets_++;

        if (categoryStats_.value(category,0) == 0) {
            categoryStats_.insert(category,1);
        }
        else {
            categoryStats_[category]++;
        }

        dataBlocks->at(numberOfPackets_-1)->SetNumOfPacket(numberOfPackets_);

        int numberOfPacket = dataBlocks->last()->GetNumOfPacket();
        QString typeOfMessage = dataBlocks->last()->GetTypeOfMessage();
        QTime timeOfReception = dataBlocks->last()->GetTimeOfReception();
        QString sicsac = dataBlocks->last()->GetSACSIC();
        QString timeToShow = "N/A";

        if (!timeOfReception.isNull()) {
            timeToShow = timeOfReception.toString("hh:mm:ss:zzz");
        }

        packetTable_->appendRow({new QStandardItem(QString::number(numberOfPacket)),new QStandardItem(QString::number(category)),
                                 new QStandardItem(QString::number(length)),new QStandardItem(sicsac),
                                 new QStandardItem(timeToShow),new QStandardItem(typeOfMessage)});
        packetTable_->setHorizontalHeaderLabels({"Packet","Category", "Length", "SAC/SIC", "Time of Transmission", "Type of Message"});
    }
    return packetDecoded;
}





