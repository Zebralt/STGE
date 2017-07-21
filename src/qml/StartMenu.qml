import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import textGame 1.0

Item {

    anchors.fill: parent

    property alias color: background.color


    Rectangle {
        id: background
        anchors.fill: parent
        color: "gray"
    }

    TabBar {
        id: header
        height: 50
        width: parent.width

        currentIndex: view.currentIndex

        TabButton {
            text: "Main"
        }

        TabButton {
            text: "Settings"

        }

        TabButton {
            text: "Data"
        }

    }

    SwipeView {
        id: view
        height: parent.height - header.height
        width: parent.width
        y: header.height
        currentIndex: header.currentIndex

        Rectangle {

            Column {
                anchors.centerIn: parent
                spacing: 5

                Text {
                    id: titlelbl
                    text: "Heavenly Door1"
                }

                Button {

                    text:"Continue"
                }

                Button {
                    text:"New Game"
                }

                Button {
                    text: "Load Game"
                }

                Button {
                    text: "Options"
                }Button {
                    text:"next"
                    onClicked: view.currentIndex= view.currentIndex + 1
                }
            }
        }

        Rectangle {
            color:"red"
            Button {
                text:"next"
                onClicked: view.currentIndex= view.currentIndex + 1
            }
        }

        Rectangle {
            color:"green"
            Button {
                      text:"next"
                      onClicked: view.currentIndex= view.currentIndex < view.count ? view.currentIndex +1 : 0
                  }
        }

    }

//    PageIndicator {
//        id: indicator

//        interactive: true
//        count: view.count
//        currentIndex: view.currentIndex
//        onCurrentIndexChanged: {
//            view.currentIndex = currentIndex
//        }

//        anchors.bottom: view.bottom
//        anchors.horizontalCenter: parent.horizontalCenter
//    }
}
