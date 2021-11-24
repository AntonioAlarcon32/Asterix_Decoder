import QtQuick 2.0
import QtQml 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.0
import QtLocation 5.12
import QtPositioning 5.6

MapItemGroup {
    id: itemGroup
    property alias position: mainCircle.center
    property var radius: 100 * 1000
    property var borderHeightPct : 0.3

    MapCircle {
        id: mainCircle
        center : QtPositioning.coordinate(40, 0)
        radius: itemGroup.radius * (1.0 + borderHeightPct)
        opacity: 0.05
        visible: true
        color: 'blue'

        MouseArea{
            anchors.fill: parent
            drag.target: parent
            id: maItemGroup
        }
    }

    MapCircle {
        id: groupCircle
        center: itemGroup.position
        radius: itemGroup.radius
        color: 'crimson'

        onCenterChanged: {
            groupPolyline.populateBorder();
        }
    }

    MapPolyline {
        id: groupPolyline
        line.color: 'green'
        line.width: 3
        function populateBorder() {
            groupPolyline.path = [] // clearing the path
            var waveLength = 8.0;
            var waveAmplitude = groupCircle.radius * borderHeightPct;
            for (var i=0; i <= 360; i++) {
                var wavePhase = (i/360.0 * 2.0 * Math.PI )* waveLength
                var waveHeight = (Math.cos(wavePhase) + 1.0) / 2.0
                groupPolyline.addCoordinate(groupCircle.center.atDistanceAndAzimuth(groupCircle.radius + waveAmplitude * waveHeight , i))
            }
        }

        Component.onCompleted: {
            populateBorder()
        }
    }
}

