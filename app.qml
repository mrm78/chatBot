import QtQuick 2.15
import QtQuick.Controls 2.15
import QtLocation 5.12
import QtPositioning 5.15
// import "https://statics.bitycle.com/devapi-public/qt"
import "heatMap"



Item {
    width: Qt.platform.os == "android" ? Screen.width : 1000
    height: Qt.platform.os == "android" ? Screen.height : 700
    visible: true

    // HeatMap {
    //     // fileUrl: "/home/mrm78/projects/qt/CustomMap/data.csv"
    //     fileUrl: "https://statics.bitycle.com/devapi-public/qt/data.csv"
    // }

    Map {
        id: map
        anchors.fill: parent
        plugin: Plugin {
            id: mapPlugin
            name: "mapboxgl"
        }
        zoomLevel: 15

        HeatMapItem {
            fileUrl: "https://statics.bitycle.com/devapi-public/qt/data.csv"
        }
    }
}