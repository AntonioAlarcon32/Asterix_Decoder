import QtQuick 2.12
import QtQml 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.0
import QtLocation 5.12
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
        property var addedItems: []
        property bool showMarkers: false

        function changeCenterPos(lat, lon) {
            testMap.center =  QtPositioning.coordinate(lat, lon)
        }

        function clearMap() {
            testMap.clearMapItems();
            testMap.addedItems = [];
        }

        function setZoom(level) {
            testMap.zoomLevel = level
        }

        function addItemToMap(lat, lon, radius, color, id) {
            var component = Qt.createComponent("PolygonGroup.qml");
            var item = component.createObject(testMap);
            item.callSign = id;
            item.position = QtPositioning.coordinate(lat, lon);
            item.radius = radius;
            item.color = color;
            if (showMarkers) {
                item.callSignVisible = true;
            }
            testMap.addMapItemGroup(item);
            testMap.addedItems.push(item);
        }

        function removeItem(id) {
            for (var i = 0; i < testMap.addedItems.length; i++) {
                if (id === testMap.addedItems[i].callSign) {
                    testMap.removeMapItemGroup(testMap.addedItems[i])
                    testMap.addedItems.splice(i,1)
                    return
                }
            }
        }
        function showCallSign() {
            testMap.showMarkers = true;
            for (var i = 0; i < testMap.addedItems.length; i++) {
                testMap.addedItems[i].setCallSign(true)
            }
        }

        function hideCallSign() {
            testMap.showMarkers = false;
            for (var i = 0; i < testMap.addedItems.length; i++) {
                testMap.addedItems[i].setCallSign(false)
            }
        }

        function clearItemsWithTwoCycles() {
            for (var i = 0; i < testMap.addedItems.length;) {
                if (1 === testMap.addedItems[i].cycles) {
                    testMap.removeMapItemGroup(testMap.addedItems[i])
                    testMap.addedItems.splice(i,1)
                }
                else {
                    testMap.addedItems[i].cycles++
                    i++
                }
            }
        }

        function getNumberOfAddedItems() {
            return addedItems.length;
        }

        function  getAddedItem(pos) {
            return addedItems[pos].callSign
        }
    }

    Plugin {
            id: mapPlugin
            name: "osm" // "mapboxgl", "esri", ...
    }
}


