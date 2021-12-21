import QtQuick 2.0
import QtQml 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.0
import QtLocation 5.12
import QtPositioning 5.6

MapItemGroup {
    id: itemGroup
    property string aircraftId: ""
    property string callSign: ""
    property string address: ""
    property string trackNumber: ""
    property string label: ""
    property alias position: marker.coordinate
    property alias radius: markerDraw.radius
    property alias color: markerDraw.color
    property bool labelVisible: false
    property int cycles: 0

    MapQuickItem {
        id: marker
        property int radius: 1
        sourceItem: Rectangle { id: markerDraw; width: radius; height: radius; color: "#002fff"; smooth: true; radius: radius }
        anchorPoint: Qt.point(sourceItem.width/2, sourceItem.height/2)
    }

    MapQuickItem {
        id: textCallSign
        sourceItem: Text{
            text: label
            color:"#242424"
            styleColor: "#ECECEC"
            style: Text.Outline
            font.pointSize: 10
        }
        coordinate: position
        anchorPoint:Qt.point(-radius,radius*2)
        visible: labelVisible
    }

    function setLabel(value) {
        itemGroup.labelVisible = value
        if (callSign != "") {
            itemGroup.label = callSign
        }
        else if (address != "") {
            itemGroup.label = address
        }
        else {
            itemGroup.label = trackNumber
        }
    }
}

