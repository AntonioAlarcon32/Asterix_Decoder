#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QMainWindow>
#include <QQuickView>
#include "QQuickItem"
#include "QGeoCoordinate"
#include "QQmlContext"
#include "custommap.h"

namespace Ui {
class TestWindow;
}

class TestWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TestWindow(QWidget *parent = nullptr);
    ~TestWindow();

private:
    Ui::TestWindow *ui;
    CustomMap *map_;

signals:
    void changePosition(double lat, double lon);
    void addMarker(double lat, double lon);
    void clearMap();
};

#endif // TESTWINDOW_H
