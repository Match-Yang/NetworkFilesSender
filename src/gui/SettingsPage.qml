import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.4

Pane {
    id: root

    property alias ip_address: si_ip_address.ip_address

    width: 200
    Material.elevation: 5
    Material.background: "#DEE5ED"
    padding: 0

    Column {
        anchors.fill: parent
        leftPadding: 10
        spacing: 5

        SettingsItemIpAddress {
            id: si_ip_address
            height: 40
            width: parent.width * 0.93
        }
    }
}
