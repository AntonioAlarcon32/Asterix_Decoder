#ifndef ASTERIXFILE_H
#define ASTERIXFILE_H

#include "QString"
#include "datablock.h"
#include "QVector"
#include "QFile"
#include "QByteRef"
#include "QStandardItemModel"
#include "cat10.h"
#include "cat19.h"
#include "cat20.h"
#include "cat21.h"

#include "appconfig.h"

class AsterixFile
{


public:
    AsterixFile();
    ~AsterixFile();

    QVector<DataBlock *> *dataBlocks;
    int numberOfPackets;
    void readFile(QString path);
    void decodeFlights();

    QStandardItemModel* table;

};


#endif // ASTERIXFILE_H
