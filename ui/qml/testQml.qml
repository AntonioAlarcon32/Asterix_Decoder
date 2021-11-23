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

    Connections {
        target: testWindow
        onChangePosition: {
            changePos(lat, lon)
        }

        onAddMarker: {
            addMarker(lat,lon)
        }

        onClearMap: {
            clearMap()
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

    Map {
        id: testMap
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(59.91, 10.75) // Oslo
        zoomLevel: 14

    }

    Component {
        id: mapCircleComponent
        MapCircle {
            id: mapCircle
            radius: 5000.0
            color: "green"
            border.width: 3
        }
    }

    function changePos(lat, lon) {
        testMap.center =  QtPositioning.coordinate(lat, lon)
    }

    function addMarker(lat, lon) {
        var circle = mapCircleComponent.createObject(testMap, {"center.latitude" : lat, "center.longitude": lon})
        testMap.addMapItem(circle)
    }

    function clearMap() {
        testMap.clearMapItems()
    }

}


