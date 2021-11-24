import QtQuick 2.0
import QtQml 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.0
import QtLocation 5.6
import QtPositioning 5.6

Rectangle {
    width: Qt.platform.os == "android" ? Screen.width : 512
    height: Qt.platform.os == "android" ? Screen.height : 512
    visible: true

    Map {
        id: testMap
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(59.91, 10.75) // Oslo
        zoomLevel: 14

        function changeCenterPos(lat, lon) {
            testMap.center =  QtPositioning.coordinate(lat, lon)
        }

        function clearMap() {
            testMap.clearMapItems()
        }

        function setZoom(level) {
            testMap.zoomLevel = level
        }
    }

    Plugin {
            id: mapPlugin
            name: "osm" // "mapboxgl", "esri", ...
            // specify plugin parameters if necessary
            // PluginParameter {
            //     name:
            //     value:
            // }
        }
}


