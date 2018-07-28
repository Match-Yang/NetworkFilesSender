import QtQuick 2.9
import QtQuick.Controls 2.4

Page {
    id: contnets_page


    TabBar {
        id: control

        PathView {
            model: control.contentModel
            currentIndex: control.currentIndex

            interactive: false
            snapMode: PathView.SnapToItem
            movementDirection: PathView.Positive
            highlightMoveDuration: 100

            path: Path {
                startX: control.count ? control.availableWidth / control.count / 2 : 0
                startY: control.availableHeight / 2
                PathLine {
                    x: control.count ? control.availableWidth + (control.availableWidth / control.count / 2) : 0
                    y: control.availableHeight / 2
                }
            }
        }

//        TabButton {
//            text: qsTr("Home")
//        }
//        TabButton {
//            text: qsTr("Discover")
//        }
//        TabButton {
//            text: qsTr("Activity")
//        }
    }
}
