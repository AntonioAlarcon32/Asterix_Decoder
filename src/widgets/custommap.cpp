#include "hdr/widgets/custommap.h"
#include "ui_custommap.h"

CustomMap::CustomMap(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomMap)
{
    ui->setupUi(this);
    QQuickWidget *view = ui->quickWidget;
    QQmlContext *context = view->rootContext();
    view->show();
    context->setContextProperty("CustomMap", this);
    screen_ = qobject_cast<QQuickItem*>(view->rootObject());
    QQuickItem *map = view->rootObject()->childItems().at(0);
    map_ = qobject_cast<QQuickItem*>(map);

}

CustomMap::~CustomMap()
{
    delete ui;
}


void CustomMap::SetPosition(WGS84Coordinates coordinates) {
    QVariant lat = coordinates.GetLatitude();
    QVariant lon = coordinates.GetLongitude();
    QMetaObject::invokeMethod(map_, "changeCenterPos",
            Q_ARG(QVariant, lat),Q_ARG(QVariant, lon));
}

void CustomMap::SetZoom(int level) {
    QVariant value = level;
    QMetaObject::invokeMethod(map_, "setZoom",
            Q_ARG(QVariant, value));
}

void CustomMap::AddCircleMarker(WGS84Coordinates coordinates, int radius, int color, QString itemId, QString callSign, QString address, QString trackNumber, double trackAngle) {
    QVariant lat = coordinates.GetLatitude();
    QVariant lon = coordinates.GetLongitude();
    QString colorCode = "";

    if (color == this->CAT21) {
        colorCode = "#002fff";
    }
    else if (color == this->CAT20) {
        colorCode = "#a600ff";
    }
    else if (color == this->CAT19) {
        colorCode = "#1eff00";
    }
    else if (color == this->CAT10MLAT) {
        colorCode = "#ff9900";
    }
    else if (color == this->CAT10SMR) {
        colorCode = "#ff0000";
    }
    QMetaObject::invokeMethod(map_, "addItemToMap", Q_ARG(QVariant, lat),Q_ARG(QVariant, lon),Q_ARG(QVariant, radius),Q_ARG(QVariant, colorCode),
                              Q_ARG(QVariant, itemId),Q_ARG(QVariant, callSign),Q_ARG(QVariant, address),Q_ARG(QVariant, trackNumber),Q_ARG(QVariant, trackAngle));
}

void CustomMap::Clear() {
    QMetaObject::invokeMethod(map_, "clearMap");
}

void CustomMap::DeleteMarker(QString id) {
    QMetaObject::invokeMethod(map_, "removeItem",Q_ARG(QVariant, id));
}

void CustomMap::ShowLabels() {
    QMetaObject::invokeMethod(map_, "showCallSign");
}

void CustomMap::HideLabels() {
    QMetaObject::invokeMethod(map_, "hideCallSign");
}

void CustomMap::ClearItemsWithTwoCycles() {
    QMetaObject::invokeMethod(map_, "clearItemsWithTwoCycles");

}

int CustomMap::GetAddedItemsLength() {
    QVariant length;
    QMetaObject::invokeMethod(map_, "getNumberOfAddedItems",Q_RETURN_ARG(QVariant, length));
    return length.toInt();
}

QString CustomMap::GetAddedItem(int pos) {
    QVariant addedItem;
    QMetaObject::invokeMethod(map_, "getAddedItem",Q_RETURN_ARG(QVariant, addedItem), Q_ARG(QVariant, pos));
    return addedItem.toString();
}

void CustomMap::SetNumberOfCycles(int number) {
    QMetaObject::invokeMethod(map_, "setNumberOfCycles", Q_ARG(QVariant, number));
}


