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
#include "otherdatablocks.h"

#include "hdr/appconfig.h"

class AsterixFile: public QObject
{
    Q_OBJECT


public:
    AsterixFile();
    ~AsterixFile();

    QVector<DataBlock *> *dataBlocks;
    int numberOfPackets;
    void decodeFlights();

    int GetTotalPackets(QString path);

    QStandardItemModel* table;

public slots:

    void readFile(QString path);

signals:

    void packetLoaded();
    void finishLoading();

};


#endif // ASTERIXFILE_H
