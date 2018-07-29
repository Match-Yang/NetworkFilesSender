import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.4

SettingsItem {
    property string ip_address: ""
    title: qsTr("Using Ip Address")
    rightContent: ComboBox {
        id: ips_box
        property var ips
        model: ips
        displayText: ips[currentIndex].address
        delegate: ItemDelegate {
            width: ips_box.width
            contentItem: Column {
                Label {
                    text: ips_box.ips[index].address
                    font.pixelSize: 13
                    elide: Text.ElideRight
                    verticalAlignment: Text.AlignVCenter
                }
                Label {
                    text: "( " + ips_box.ips[index].name + " )"
                    font.pixelSize: 10
                    elide: Text.ElideRight
                    verticalAlignment: Text.AlignVCenter
                }
            }

            highlighted: ips_box.highlightedIndex === index

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    ips_box.popup.close()
                    ips_box.currentIndex = index

                    ip_address = ips_box.displayText
                    // record to configure file after changed
                    settings_manager.setValue("SettingsItem", "IpAddress",
                                              ip_address)
                }
            }
        }

        Component.onCompleted: {
            ips = device_info_collector.getIpAddresses()
            var cip = settings_manager.value("SettingsItem", "IpAddress")
            var i
            for (i = 0; i < ips.length; i++) {
                if (cip === ips[i].address) {
                    ips_box.currentIndex = i
                    break
                }
            }

            ip_address = displayText
        }
    }
}
