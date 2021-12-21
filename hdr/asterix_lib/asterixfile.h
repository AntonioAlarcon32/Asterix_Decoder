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

    QVector<DataBlock *> *dataBlocks;
    QList<Emitter> emitters_;
    int numberOfPackets_;
    QList<int> filteredPackets_;
    void decodeFlights();


    int GetTotalPackets(QString path);

    void ResetFilters();
    void FilterByCallSign(QString callSign, QList<int> &packetList);
    void FilterByCategory(int category,QList<int> &packetList);
    void FilterByAddress(QString address,QList<int> &packetList);
    void FilterByTrackNumber(int trackNumber,QList<int> &packetList);
    void FilterByMode3A(int mode3ACode,QList<int> &packetList);
    bool AddPacketToList(QByteArray data);

    void ApplyFilters(int category = -1, QString callSign = "", QString address = "", int trackNumber = -1, int mode3ACode = -1);


    QStandardItemModel* packetTable_;
    QStandardItemModel* emitterTable_;
    QFileInfo fileInfo_;
    QMap<int,int> categoryStats_;
    void writeFile(QString path);

public slots:

    void readFile(QString path);
    void ProcessEmitters();

signals:

    void packetLoaded();
    void finishLoading();

};


#endif // ASTERIXFILE_H
