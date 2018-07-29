import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.4

Pane {
    id: sitem

    property alias title: title_label.text
    property Component rightContent

    height: 30
//    Material.elevation: 5
    padding: 0

    Label {
        id: title_label
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width / 2
        height: parent.height
        verticalAlignment: Text.AlignVCenter
    }

    Loader {
        id: content_loader
        active: true
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width / 2
        height: parent.height
        sourceComponent: rightContent
    }
}
