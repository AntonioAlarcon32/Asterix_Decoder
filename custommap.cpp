#include "custommap.h"
#include "ui_custommap.h"

CustomMap::CustomMap(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomMap)
{
    ui->setupUi(this);
    QQuickWidget *view = ui->quickWidget;
    QQmlContext *context = view->rootContext();
    view->show();
    context->setContextProperty("customMap", this);
    screen_ = qobject_cast<QQuickItem*>(view->rootObject());
    QQuickItem *map = view->rootObject()->childItems().at(0);
    map_ = qobject_cast<QQuickItem*>(map);
}

CustomMap::~CustomMap()
{
    delete ui;
}


void CustomMap::SetPosition(WGS84Coordinates coordinates) {
    QVariant lat = coordinates.latitude;
    QVariant lon = coordinates.longitude;
    QMetaObject::invokeMethod(map_, "changeCenterPos",
            Q_ARG(QVariant, lat),Q_ARG(QVariant, lon));
}

void CustomMap::SetZoom(int level) {
    QVariant value = level;
    QMetaObject::invokeMethod(map_, "setZoom",
            Q_ARG(QVariant, value));
}

void CustomMap::AddCircleMarker(WGS84Coordinates coordinates, int radius, QString color) {
    QVariant lat = coordinates.latitude;
    QVariant lon = coordinates.longitude;
    QMetaObject::invokeMethod(map_, "addItemToMap", Q_ARG(QVariant, lat),Q_ARG(QVariant, lon),Q_ARG(QVariant, radius),Q_ARG(QVariant, color));
}

void CustomMap::Clear() {
    QMetaObject::invokeMethod(map_, "clearMap");
}


