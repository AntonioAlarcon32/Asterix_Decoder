#ifndef ASTERIXFILE_H
#define ASTERIXFILE_H

#include "QString"
#include "QElapsedTimer"
#include "QFileInfo"
#include "QDebug"
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
#include "emitter.h"

#include "hdr/appconfig.h"

class AsterixFile: public QObject
{
    Q_OBJECT


public:
    AsterixFile();
    ~AsterixFile();

    QList<DataBlock*> *dataBlocks;
    QList<Emitter> emitters_;
    int numberOfPackets_;
    QList<DataBlock*> filteredPackets_;
    void decodeFlights();


    int GetTotalPackets(QString path);

    void ResetFilters();
    void FilterByCallSign(QString callSign, QList<DataBlock*> &packetList);
    void FilterByCategory(int category,QList<DataBlock*> &packetList);
    void FilterByAddress(QString address,QList<DataBlock*> &packetList);
    void FilterByTrackNumber(int trackNumber,QList<DataBlock*> &packetList);
    void FilterByMode3A(int mode3ACode,QList<DataBlock*> &packetList);
    bool AddPacketToList(QByteArray data);

    void ApplyFilters(int category = -1, QString callSign = "", QString address = "", int trackNumber = -1, int mode3ACode = -1);


    QStandardItemModel* packetTable_;
    QStandardItemModel* emitterTable_;
    QFileInfo fileInfo_;
    QMap<int,int> categoryStats_;
    void writeFile(QString path, bool saveAll);

public slots:

    void readFile(QString path);
    void ProcessEmitters();

signals:

    void packetLoaded();
    void finishLoading();

};


#endif // ASTERIXFILE_H
