#include <hdr/asterix_lib/asterixfile.h>
#include "QElapsedTimer"
#include "QFileInfo"
#include "QDebug"


AsterixFile::AsterixFile()
{
    dataBlocks = new QVector<DataBlock*>();
}


void AsterixFile::readFile(QString path) {

    dataBlocks->clear();

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

        }  catch (...) {

            qDebug() << "ERROR IN PACKET" << numOfPackets + 1;

        }

        //Cat10 *inten = static_cast<Cat10*>(dataBlocks->at(0));
        //Cat10 *inten2 = dynamic_cast<Cat10*>(dataBlocks->at(0));

        numOfPackets++;
        offset += length;
        if (fileInfo.completeSuffix() == "gps") {
            offset += 10;
        }
    }

     qDebug() << "Loading took" << testTime->elapsed() << "milliseconds";
     qDebug() << "Loaded " << numOfPackets << " packets";
     this->numberOfPackets = numOfPackets;
}
