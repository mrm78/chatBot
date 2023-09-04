import QtQuick 2.15
import QtQuick.Controls 2.15
import QtLocation 5.15
import QtPositioning 5.15



Map {
    id: map
    anchors.fill: parent
    plugin: Plugin {
        id: mapPlugin
        name: "mapboxgl"
    }
    zoomLevel: 15
    property var fileUrl

    HeatMapItem {
        fileUrl: map.fileUrl
    }

}
