#ifndef CUSTOMMAP_H
#define CUSTOMMAP_H

#include <QWidget>
#include "QQmlContext"
#include "QQuickWidget"
#include "QQuickItem"
#include "wgs84coordinates.h"

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
    void DeleteMarker(QString id);

private:
    Ui::CustomMap *ui;
    QQuickItem *map_;
    QQuickItem *screen_;

};

#endif // CUSTOMMAP_H
