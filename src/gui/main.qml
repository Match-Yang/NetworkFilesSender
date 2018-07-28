import QtQuick 2.9
import QtQuick.Controls 2.2

ApplicationWindow {
    id: window
    visible: true

    width: 1024
    height: 600
    background: Rectangle {
        color: "#f8f8f8"
    }

    ContentsPage {
        id: contents_page
        leftPadding: nav_page.width
        anchors.fill: parent
    }

    NavigationPage {
        id: nav_page
        width: 260
        height: parent.height
        anchors.left: parent.left
    }

    Component.onCompleted: {
        var ips = device_info_collector.getIpAddresses()
        console.log(ips)
        for (var i = 0; i < ips.length; i++) {
            console.log("Array item:", ips[i].name)
            console.log("Array item:", ips[i].address)
        }
    }
}
