#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QMainWindow>
#include <QQuickView>
#include "QQuickItem"
#include "QGeoCoordinate"
#include "QQmlContext"

namespace Ui {
class TestWindow;
}

class TestWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TestWindow(QWidget *parent = nullptr);
    ~TestWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::TestWindow *ui;
    QQuickItem *map_;

signals:
    void changePosition(double lat, double lon);
    void addMarker(double lat, double lon);
    void clearMap();
};

#endif // TESTWINDOW_H
