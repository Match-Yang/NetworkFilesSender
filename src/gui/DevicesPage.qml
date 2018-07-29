import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.4

Pane {
    id: root

    width: 200
    Material.elevation: 5
    Material.background: "#DEE5ED"
    padding: 0

    Rectangle {
        width: 20
        height: 20
        color: "red"
        anchors.centerIn: parent
    }
}
