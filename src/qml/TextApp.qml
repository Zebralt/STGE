import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import textGame 1.0

Item {

    property alias color: background.color
    property string text: textGame.scene

    onTextChanged: {
//        glyphText.text = text.charAt(0)
        contentText.text = text
    }

    anchors.fill: parent

    function initialize() {
        textGame.initialize()
    }

    function pick(txt) {
        textGame.proceed(txt)
    }

    FontLoader {
        id: latinfl

        source: "qrc:../resources/Latin-Modern-Roman/lmroman10-regular.otf"
    }

    Rectangle {
        id: background

        anchors.fill: parent
    }

    property TextGame game: TextGame {
        id: textGame

        Component.onCompleted: {
            appwindow.visible = true
            initialize()
        }
    }

    Rectangle {
        id: content

        anchors.fill: parent
        anchors.margins: 5

        Column {

            anchors.fill: parent
            anchors.margins: 1
            spacing: 2

            Rectangle {
                height: 25
                width: parent.width
                color: "#DDD"

                Text {
                    id: titleText
                    text: textGame.scene_title
//                    font.family: latinfl.name
                    anchors.centerIn: parent
                }
            }

            Rectangle {
               width: parent.width
               height: 400
               color: "#EEE"
                Row {
                    anchors.fill: parent
                    anchors.margins: 10

//                    FontLoader {
//                        id: glyphFont
//    //                    source:"D:\textgame_data\arial.ttf"
//                        name: "Courier"
//                    }

//                    Text {
//                        id: glyphText
//                        height: parent.height
//                        width: parent.width/3
//                        font.family: glyphFont.name
//                    }

//                    Rectangle {
//                        color: "gray"
//                        width: 1
//                        height: parent.height
//                    }

//                    Rectangle {
//                        color:"transparent"
//                        width: 10
//                        height: parent.height
//                    }

                    Text {
                        id: contentText

                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        text: textGame.scene
                        height: parent.height
                        width: parent.width/2
                        anchors.centerIn: parent

//                        font.family: latinfl.name
//                        font.pointSize: 12


                    }
                }
            }

            Row {
                spacing: 2

                Repeater {
                    id:lview

                    model: textGame.choices

                    Button {
                        id: control

                        text: modelData
                        onClicked: {
                            pick(text)
                        }

                        contentItem: Text {
                            text: control.text
                            font: control.font
                            opacity: enabled ? 1.0 : 0.3
//                            color: control.down ? "#17a81a" : "#21be2b"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            elide: Text.ElideRight
                        }

                        background: Rectangle {
                            implicitWidth: 100
                            opacity: enabled ? 1 : 0.3
//                            border.color: control.down ? "#17a81a" : "#21be2b"
                            border.color: "#ddd"
                            border.width: 1
                            radius: 2
                        }
                    }
                }
            }
        }
    }
}
