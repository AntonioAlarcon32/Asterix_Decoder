#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QMainWindow>
#include <QQuickView>
#include "QQuickItem"
#include "QGeoCoordinate"
#include "QQmlContext"
#include "hdr/widgets/custommap.h"

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

signals:
    void changePosition(double lat, double lon);
    void addMarker(double lat, double lon);
    void clearMap();
private slots:
    void on_toolButton_clicked();
};

#endif // TESTWINDOW_H
