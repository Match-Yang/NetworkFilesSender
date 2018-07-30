import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.4

Pane {
    id: ditem

    property var dinfo
    property string name_color: Material.foreground

    signal clicked

    height: 40
    width: 260
    Material.elevation: 5
    padding: 5

    Column {
        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 5
        spacing: 5
        Label {
            id: device_name_label
            font.bold: true
            font.pixelSize: 15
            text: dinfo.devide_name
            elide: Text.ElideRight
            color: name_color
        }

        Label {
            id: device_ip
            text: dinfo.ip_address
        }
    }

    Image {
        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.right: parent.right
        width: 16
        height: 16
        source: "qrc:/images/menu_vertical_48.png"
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            ditem.clicked()
        }
    }
}
