import QtQuick 2.0
import QtQml 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.0
import QtLocation 5.12
import QtPositioning 5.6

MapItemGroup {
    id: itemGroup
    property alias position: marker.coordinate
    property alias radius: markerDraw.radius
    property alias color: markerDraw.color

    MapQuickItem {
            id: marker
            property int radius: 1
            sourceItem: Rectangle { id: markerDraw; width: radius; height: radius; color: "red"; smooth: true; radius: radius }
            anchorPoint: Qt.point(sourceItem.width/2, sourceItem.height/2)
        }
}

