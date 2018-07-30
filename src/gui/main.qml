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
        leftPadding: nav_page.width + config_swipe.width
        anchors.fill: parent
    }

    SwipeView {
        id: config_swipe
        orientation: Qt.Vertical
        anchors.left: nav_page.right
        height: parent.height
        width: 300

        DevicesPage {

        }
        SettingsPage {
            id: settings_page
        }

        currentIndex: nav_page.page_index
    }

    NavigationPage {
        id: nav_page
//        width: 260
        current_ip: settings_page.ip_address
        height: parent.height
        anchors.left: parent.left
    }
}
