#ifndef CUSTOMMAP_H
#define CUSTOMMAP_H

#include <QWidget>
#include "QQmlContext"
#include "QQuickWidget"
#include "QQuickItem"
#include "hdr/wgs84coordinates.h"

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
    void AddCircleMarker(WGS84Coordinates coordinates, int radius, QString color, QString id);
    void Clear();
    void ClearItemsWithTwoCycles();
    void DeleteMarker(QString id);
    void ShowLabels();
    void HideLabels();
    int GetAddedItemsLength();
    QString GetAddedItem(int pos);

private:
    Ui::CustomMap *ui;
    QQuickItem *map_;
    QQuickItem *screen_;

};

#endif // CUSTOMMAP_H
