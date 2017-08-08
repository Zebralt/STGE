import QtQuick 2.7
import QtQuick.Controls 2.0
//import QtQuick.Extras 1.4
import QtQuick.Layouts 1.0
import textGame 1.0

ApplicationWindow {
    id: appwindow
    visible: true
    width: 640
    height: 480

    /*TextApp {
        id: textApp
    }*/

//    Loader {
//        id: pageLoader
//    }

//    Row {

//        spacing: 5
//        Button {
//            text:"Click me"
//            onClicked: pageLoader.source = "TextApp.qml"
//        }
//        Button {
//            text:"Don't click me"
//            onClicked:pageLoader.source =""
//        }
//    }

    TextApp {

    }

    StartMenu {
        visible: false
    }

}


/*
    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page1 {
        }

        Page {
            Label {
                text: qsTr("Second page")
                anchors.centerIn: parent
            }
        }

        PageIndicator {
            currentIndex: swipeView.currentIndex
            count: swipeView.count
            interactive: true
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    header: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("First")
        }
        TabButton {
            text: qsTr("Second")
        }
    }*/
