import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.4

Pane {
    id: root
    property string current_ip: "127.0.0.1"
    property int page_index: 0

    width: 200
    Material.elevation: 5
    padding: 0

    Component.onCompleted: {
        root.state = settings_manager.value("NavigationPage", "CurrentState", "simple")
    }

    states: [
        State {
            name: "simple"
            PropertyChanges{target: root; width: 100}
            PropertyChanges {target: header_labels; visible: false}
            PropertyChanges {target: discover_switch; text: ""}
        },
        State {
            name: "details"
            PropertyChanges{target: root; width: 260}
            PropertyChanges {target: header_labels; visible: true}
            PropertyChanges {target: discover_switch; text: qsTr("Enable Discover")}
        }
    ]

    Frame {
        id: header_frame
        height: 60
        padding: 10
        // There is a border around frame by default
        background: Item {
        }

        Rectangle {
            id: icon_rect
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            height: parent.height * 4 / 5
            width: height
            radius: height / 4

            //            border.color: "#bfbfbf"
            //            border.width: 3
            Image {
                source: getDeviceIcons(device_info_collector.getDeviceType())
                anchors.centerIn: parent
                width: parent.width
                height: parent.height
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (root.state == "simple") {
                        root.state = "details"
                        settings_manager.setValue("NavigationPage", "CurrentState", "details")
                    } else {
                        root.state = "simple"
                        settings_manager.setValue("NavigationPage", "CurrentState", "simple")
                    }
                }
            }
        }

        Item {
            id: header_labels
            height: parent.height
            anchors.left: icon_rect.right
            anchors.leftMargin: 15
            anchors.verticalCenter: icon_rect.verticalCenter
            Label {
                text: device_info_collector.getDeviceName()
                anchors.bottom: parent.verticalCenter
                font.pixelSize: 12
                color: "#323c46"
            }

            Label {
                text: current_ip
                anchors.top: parent.verticalCenter
                font.pixelSize: 10
                color: "#bfbfbf"
            }
        }
    }

    Rectangle {
        id: sep
        height: 2
        width: parent.width
        color: "#f2f2f2"
        anchors.top: header_frame.bottom
    }

    GroupBox {
        height: parent.height - header_frame.height - sep.height
        width: parent.width
        anchors.bottom: parent.bottom
        padding: 0
        background: Item {
        }

        Column {
            anchors.fill: parent
            anchors.topMargin: spacing
            padding: 0
            spacing: 10

            TabButton {
                id: devices_button
                text: qsTr("Devices")
                height: 35
                width: parent.width
                onClicked: page_index = 0
            }
            TabButton {
                id: settings_button
                text: qsTr("Settings")
                height: 35
                width: parent.width
                onClicked: page_index = 1
            }
        }
    }

    Switch {
        id: discover_switch
        width: parent.width * 3 / 4
        height: 50
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        text: qsTr("Enable Discover")
        onCheckedChanged: {
            console.log("Checked", checked)
            if (checked) {
                discover_manager.setDeviceInfo(getDeviceInfo())
            }
            discover_manager.enableDicover(checked)
        }
    }

    function getDeviceIcons(dt) {
        var image_map = {
            osx: "qrc:/images/device_osx.png",
            windows: "qrc:/images/device_windows.png"
        }
        return image_map[dt]
    }

    function getDeviceInfo() {
        var infos = {
            ip_address: current_ip,
            devide_name: device_info_collector.getDeviceName(),
            devide_type: device_info_collector.getDeviceType(),
            storage_capability: device_info_collector.getStorageCapability(),
            storage_free: device_info_collector.getStorageFree()
        }
        return infos;
    }
}
