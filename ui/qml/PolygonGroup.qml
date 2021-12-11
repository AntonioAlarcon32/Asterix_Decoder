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
    property string callSign: ""
    property bool callSignVisible: false
    property int cycles: 0

    MapQuickItem {
        id: marker
        property int radius: 1
        sourceItem: Rectangle { id: markerDraw; width: radius; height: radius; color: "red"; smooth: true; radius: radius }
        anchorPoint: Qt.point(sourceItem.width/2, sourceItem.height/2)
    }

    MapQuickItem {
        id: textCallSign
        sourceItem: Text{
            text: callSign
            color:"#242424"
            styleColor: "#ECECEC"
            style: Text.Outline
            font.pointSize: 10
        }
        coordinate: position
        anchorPoint:Qt.point(-radius,radius*2)
        visible: callSignVisible
    }

    function setCallSign(value) {
        itemGroup.callSignVisible = value
    }
}

