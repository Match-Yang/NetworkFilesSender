import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.4

Pane {

    property string current_ip: "127.0.0.1"

    width: 200
    Material.elevation: 5
    padding: 0

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
        }

        Label {
            text: device_info_collector.getDeviceName()
            anchors.left: icon_rect.right
            anchors.leftMargin: 15
            anchors.top: icon_rect.top
            font.pixelSize: 12
            color: "#323c46"
        }

        Label {
            text: current_ip
            anchors.left: icon_rect.right
            anchors.leftMargin: 15
            anchors.bottom: icon_rect.bottom
            font.pixelSize: 10
            color: "#bfbfbf"
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
                id: settings_button
                text: qsTr("Settings")
                height: 35
                width: parent.width
            }

            TabButton {
                id: devices_button
                text: qsTr("Devices")
                height: 35
                width: parent.width
            }
        }
    }

    Switch {

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
