#include <hdr/asterix_lib/asterixfile.h>
#include "QElapsedTimer"
#include "QDebug"


AsterixFile::AsterixFile()
{
    dataBlocks = new QVector<DataBlock*>();

}


void AsterixFile::readFile(QString path) {

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) return;
    QByteArray fileBinary = file.readAll();
    int numOfPackets = 0;
    QElapsedTimer* testTime = new QElapsedTimer();
    testTime->start();

    for (int offset = 0; offset < fileBinary.length(); ) {

        int category = fileBinary[offset];
        int length =  fileBinary[offset + 2] << fileBinary[offset + 1] ;
        QVector<unsigned char> data(QVector<unsigned char>(length - 3));

        if (category == 10) {

            Cat10 *cat10Block = new Cat10();
            cat10Block->SetLength(length);
            for (int i = 3; i < length; i++) {
                data[i-3] = fileBinary.at(offset + i);
            }
            cat10Block->SetData(data);
            cat10Block->DecodeFSPEC();
            cat10Block->FullDecode();
            dataBlocks->append(cat10Block);
        }

        else if (category == 21) {
            Cat21 *cat21Block = new Cat21();
            cat21Block->SetLength(length);
            for (int i = 3; i < length; i++) {
                data[i-3] = fileBinary.at(offset + i);
            }
            cat21Block->SetData(data);
            cat21Block->DecodeFSPEC();
            dataBlocks->append(cat21Block);
        }

        //Cat10 *inten = static_cast<Cat10*>(dataBlocks->at(0));
        //Cat10 *inten2 = dynamic_cast<Cat10*>(dataBlocks->at(0));
        numOfPackets++;
        offset += length;
    }
     qDebug() << "Loading took" << testTime->elapsed() << "milliseconds";
     qDebug() << "Loaded " << numOfPackets << " packets";
}
