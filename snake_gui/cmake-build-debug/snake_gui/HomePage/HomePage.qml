import QtQuick
import QtQuick.Controls
import QtMultimedia 6.0

Rectangle {
    color: "transparent"

    //FontLoader { id: hpFontLoader; source: "fonts/retro.ttf" }

    MediaPlayer {
        id: btnSoundPlayer
        source: "qrc:/snake_gui/sounds/button.mp3"  // Path to the music file
        audioOutput: AudioOutput {
            volume: 0.5
        }

    }

    Column {
        anchors.fill: parent
        Row {
            id: settingsRow
            height: 200
            width: parent.width
            leftPadding: 60
            topPadding: 60
            Button {
                id: settingsBtn
                width: 80
                height: 80

                MouseArea {
                    id: settingsBtnMouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        btnSoundPlayer.stop();
                        btnSoundPlayer.play();
                    }
                }

                background: Image {
                    id: settingsBtnBackground
                    anchors.fill: parent
                    source:  settingsBtnMouseArea.containsPress ? "../images/UI-105.png" :"../images/UI-104.png"
                    fillMode: Image.Stretch
                }
            }
        }
        Column {
            width:parent.width
            height: parent.height - settingsRow.height

            Image {
                id: logo
                width: 400
                height: 300
                anchors.horizontalCenter: parent.horizontalCenter
                source: "../images/snakes_logo.png"
                fillMode: Image.Stretch
            }

            Button {
                id: newGameBtn
                width: 300
                height: 100
                anchors.horizontalCenter: parent.horizontalCenter

                MouseArea {
                    id: newGameBtnMouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        btnSoundPlayer.stop();
                        btnSoundPlayer.play();
                    }
                }

                background: Rectangle {
                    anchors.fill: newGameBtn
                    color: "transparent"
                    Image {
                        id: newGameBtnBackground
                        anchors.fill: parent
                        source: newGameBtnMouseArea.containsPress ? "../images/UI-05.png" : "../images/UI-06.png"
                        fillMode: Image.Stretch
                    }
                    Text {
                        z:2
                        horizontalAlignment: Text.AlignHCenter
                        text: "New Game"
                        font.family: "Retro Gaming"
                        font.pixelSize: 40
                        color: "#ffffff"
                        width: parent.width
                        height: 40
                        y: newGameBtnMouseArea.containsPress ? parent.y + 28 : parent.y + 20
                    }
                }
            }

            Button {
                id: connectBtn
                width: 300
                height: 100
                anchors.horizontalCenter: parent.horizontalCenter

                MouseArea {
                    id: connectBtnMouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        btnSoundPlayer.stop();
                        btnSoundPlayer.play();
                    }
                }

                background: Rectangle {
                    anchors.fill: connectBtn
                    color: "transparent"
                    Image {
                        id: connectBtnBackground
                        anchors.fill: parent
                        source: connectBtnMouseArea.containsPress ? "../images/UI-04.png" : "../images/UI-03.png"
                        fillMode: Image.Stretch
                    }
                    Text {
                        z:2
                        horizontalAlignment: Text.AlignHCenter
                        text: "Connect"
                        font.family: "Retro Gaming"
                        font.pixelSize: 40
                        color: "#ffffff"
                        width: parent.width
                        height: 40
                        y: connectBtnMouseArea.containsPress ? parent.y + 28 : parent.y + 20
                    }
                }
            }
        }
    }
}