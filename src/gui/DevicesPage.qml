import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.4

Pane {
    id: root

    width: 200
    Material.elevation: 5
    Material.background: "#DEE5ED"
    padding: 0

    Component {
        id: highlight_comp
        DevicesItem {
            dinfo: discover_manager.others_devices[devices_list.currentIndex]
            anchors.horizontalCenter: parent.horizontalCenter
            z: 1
            name_color: Material.accent
            height: 100
            width: devices_list.width * 3 / 4
            y: devices_list.currentItem.y
            Behavior on y {
                SpringAnimation {
                    spring: 1
                    damping: 0.2
                }
            }
        }
    }
    ListView {
        id: devices_list
        anchors.fill: parent
        model: discover_manager.others_devices
        spacing: 10
        topMargin: 10
        bottomMargin: 10
//        highlight: highlight_comp
        delegate: DevicesItem {
            name_color: index == devices_list.currentIndex ? Material.accent : Material.foreground
            dinfo: discover_manager.others_devices[index]
            anchors.horizontalCenter: parent.horizontalCenter
            height: 60
            width: parent.width * 3 / 4
            onClicked: {
                devices_list.currentIndex = index
            }
        }
    }

    Connections {
        target: discover_manager
        onOthersDevicesChanged: {
            console.log(discover_manager.others_devices,
                        discover_manager.others_devices.length)
        }
    }
}
