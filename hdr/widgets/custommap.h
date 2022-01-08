#ifndef CUSTOMMAP_H
#define CUSTOMMAP_H

#include <QWidget>
#include "QQmlContext"
#include "QQuickWidget"
#include "QQuickItem"
#include "hdr/asterix_lib/wgs84coordinates.h"

namespace Ui {
class CustomMap;
}

class CustomMap : public QWidget
{
    Q_OBJECT

public:
    explicit CustomMap(QWidget *parent = nullptr);
    ~CustomMap();

    void SetPosition(WGS84Coordinates coordinates);
    void SetZoom(int level);
    void AddCircleMarker(WGS84Coordinates coordinates, int radius, int color, QString itemId, QString callSign, QString address, QString trackNumber, double trackAngle);
    void Clear();
    void ClearItemsWithTwoCycles();
    void DeleteMarker(QString id);
    void ShowLabels();
    void HideLabels();
    void SetNumberOfCycles(int number);
    int GetAddedItemsLength();
    QString GetAddedItem(int pos);

    enum Colors {
        CAT21 = 21,
        CAT20 = 20,
        CAT19 = 19,
        CAT10MLAT = 101,
        CAT10SMR = 102
    };

private:
    Ui::CustomMap *ui;
    QQuickItem *map_;
    QQuickItem *screen_;

};

#endif // CUSTOMMAP_H
