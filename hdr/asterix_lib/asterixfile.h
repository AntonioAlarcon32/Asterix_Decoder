#ifndef ASTERIXFILE_H
#define ASTERIXFILE_H

#include "QString"
#include "datablock.h"
#include "QVector"
#include "QFile"
#include "QByteRef"
#include "cat10.h"
#include "cat21.h"

class AsterixFile
{


public:
    AsterixFile();

    QVector<DataBlock *> *dataBlocks;
    void readFile(QString path);
    void decodeFlights();

};


#endif // ASTERIXFILE_H
