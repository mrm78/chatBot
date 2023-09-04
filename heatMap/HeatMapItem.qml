import QtQuick 2.15
import QtQuick.Controls 2.15
import QtLocation 5.15
import QtPositioning 5.15

Item {
    id: heatMap

    property var fileUrl

    // read csv file and extract points
    function readCsv(fileUrl)
    {
        var xhr = new XMLHttpRequest();
        xhr.open("GET", fileUrl, false);
        xhr.send();
        if (xhr.status === 200)
        {
            var lines = xhr.responseText.trim().split("\n");
            var points = [];
            for (var i = 0; i < lines.length; i++) {
                var fields = lines[i].split(",");
                fields[0] = (Math.abs(fields[0]) - 50) / 100
                if (fields.length > 0 && i%5==0)
                    points.push(fields);
            }
            return points.slice(0, 1000);
        } else {
        console.error("Failed to read CSV file:", xhr.statusText);
        return [];
    }
}
property var points: readCsv(fileUrl)

Component.onCompleted: {
    // set first point as map center
    var center = QtPositioning.coordinate(points[0][2], points[0][3]);
    parent.center = center;

    // create circle objects based on given points and add to map 
    for (var index = 0; index < heatMap.points.length; index++) {
        var circle = Qt.createQmlObject('import QtLocation 5.15; MapCircle {}', parent)
        circle.center = QtPositioning.coordinate(heatMap.points[index][2], heatMap.points[index][3])
        circle.radius = 10
        var intensity = heatMap.points[index][0]
        circle.color = Qt.rgba(intensity, 0, 1-intensity, 1)
        circle.border.width = 0
        parent.addMapItem(circle)
    }
}

}