import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import textGame 1.0

Item {

    property alias color: background.color
    property string text: textGame.scene

    onTextChanged: {
        glyphText.text = text.charAt(0)
        contentText.text = text
    }

    anchors.fill: parent

    function initialize() {
        textGame.initialize()
    }

    function pick(txt) {
        textGame.proceed(txt)
    }

    Rectangle {
        id: background

        anchors.fill: parent
    }

    property TextGame game: TextGame {
        id: textGame
        title: "textgame"
        Component.onCompleted: {
            appwindow.visible = true
            initialize()
        }
    }

    Column {

        anchors.fill: parent
        spacing: 3

        Text {
            id: titleText
            text: textGame.scene_title
        }

        Rectangle {
            height: 2
            width: parent.width
            color: "gray"
        }

        Rectangle {
           height: 400
           width: parent.width
            Row {
                anchors.fill: parent

                FontLoader {
                    id: glyphFont
//                    source:"D:\textgame_data\arial.ttf"
                    name: "Courier"
                }

                Text {
                    id: glyphText
                    height: parent.height
                    width: parent.width/3
                    font.family: glyphFont.name
                }

                Rectangle {
                    color: "gray"
                    width: 1
                    height: parent.height
                }

                Rectangle {
                    color:"transparent"
                    width: 10
                    height: parent.height
                }

                Text {
                    id: contentText

                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    text: textGame.scene
                    height: parent.height
                    width: parent.width/2
                }
            }
        }

        Rectangle {
            height: 2
            width: parent.width
            color: "gray"
        }

        Row {
            spacing: 2
            Repeater {
                id:lview

                model: textGame.choices

                Button {
                    text: modelData
                    onClicked: {
                        pick(text)
                    }
                }
            }
        }


    }
}
