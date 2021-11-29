#include <hdr/asterix_lib/asterixfile.h>
#include "QElapsedTimer"
#include "QFileInfo"
#include "QDebug"


AsterixFile::AsterixFile()
{
    dataBlocks = new QVector<DataBlock*>();
    packetTable_ = new QStandardItemModel;
    emitterTable_ = new QStandardItemModel;
    emitters_ = QList<Emitter>();
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
        return;
    }

    for (; offset < fileBinary.length(); ) {


        int category = fileBinary[offset];
        int length =  fileBinary[offset + 2] << fileBinary[offset + 1] ;

        try {

            if (category == 10) {

                Cat10 *cat10Block = new Cat10();
                cat10Block->SetLength(length);
                QByteArray data = fileBinary.mid(offset + 3,length - 3);
                cat10Block->SetData(data);
                cat10Block->DecodeFSPEC();
                cat10Block->FullDecode();
                dataBlocks->append(cat10Block);
            }

            else if (category == 19) {
                Cat19 *cat19Block = new Cat19();
                cat19Block->SetLength(length);
                QByteArray data = fileBinary.mid(offset + 3,length - 3);
                cat19Block->SetData(data);
                cat19Block->DecodeFSPEC();
                cat19Block->FullDecode();
                dataBlocks->append(cat19Block);

            }

            else if (category == 20) {
                Cat20 *cat20Block = new Cat20();
                cat20Block->SetLength(length);
                QByteArray data = fileBinary.mid(offset + 3,length - 3);
                cat20Block->SetData(data);
                cat20Block->DecodeFSPEC();
                cat20Block->FullDecode();
                dataBlocks->append(cat20Block);

            }

            else if (category == 21) {
                Cat21 *cat21Block = new Cat21();
                cat21Block->SetLength(length);
                QByteArray data = fileBinary.mid(offset + 3,length - 3);
                cat21Block->SetData(data);
                cat21Block->DecodeFSPEC();
                cat21Block->FullDecode();
                dataBlocks->append(cat21Block);
            }

            else {

                OtherDataBlocks *other = new OtherDataBlocks(category);
                other->SetLength(length);
                QByteArray data = fileBinary.mid(offset + 3,length - 3);
                other->SetData(data);
                dataBlocks->append(other);
            }

        }  catch (...) {

            qDebug() << "ERROR IN PACKET" << numOfPackets + 1;

        }

        //Cat10 *inten = static_cast<Cat10*>(dataBlocks->at(0));
        //Cat10 *inten2 = dynamic_cast<Cat10*>(dataBlocks->at(0));

        numOfPackets++;
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
        packetTable_->appendRow({new QStandardItem(QString::number(numOfPackets)),new QStandardItem(QString::number(category)),new QStandardItem(QString::number(length)),new QStandardItem(sicsac),
                          new QStandardItem(timeToShow),new QStandardItem(typeOfMessage)});
        offset += length;
        if (fileInfo.completeSuffix() == "gps") {
            offset += 10;
        }
    }
    packetTable_->setHorizontalHeaderLabels({"Packet","Category", "Length", "SAC/SIC", "Time of Transmission", "Type of Message"});

    this->ProcessEmitters();

    emit finishLoading();
     qDebug() << "Loading took" << testTime->elapsed() << "milliseconds";
     qDebug() << "Loaded " << numOfPackets << " packets";
     this->numberOfPackets = numOfPackets;
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
            if (i == 42)
                int c = 1;

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

void AsterixFile::FilterByCallSign(QString callSign) {

    packetTable_->clear();

    for (DataBlock *dataBlock : *dataBlocks) {

        if (callSign == dataBlock->GetCallSign().replace(" ","")) {

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

            packetTable_->appendRow({new QStandardItem(QString::number(packetNumber)),new QStandardItem(QString::number(category)),new QStandardItem(QString::number(length)),new QStandardItem(sicsac),
                                     new QStandardItem(timeToShow),new QStandardItem(typeOfMessage)});
        }
    }

    packetTable_->setHorizontalHeaderLabels({"Packet","Category", "Length", "SAC/SIC", "Time of Transmission", "Type of Message"});

}




