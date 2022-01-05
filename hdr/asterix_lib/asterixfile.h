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
    void FilterByCallSign(QStringList callSign, QList<DataBlock*> &packetList);
    void FilterByCategory(QList<int> category,QList<DataBlock*> &packetList);
    void FilterByAddress(QStringList address,QList<DataBlock*> &packetList);
    void FilterByTrackNumber(QList<int> trackNumber,QList<DataBlock*> &packetList);
    void FilterByMode3A(QList<int> mode3ACode,QList<DataBlock*> &packetList);
    bool AddPacketToList(QByteArray data);

    void ApplyFilters(QList<int> category, QStringList callSign, QStringList address, QList<int> trackNumber, QList<int> mode3ACode);


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
