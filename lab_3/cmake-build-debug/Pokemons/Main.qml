import QtQuick
import QtQuick.Controls
import Qt.labs.qmlmodels

import btnMdl
import tblMdl

Window {
    width: 300
    height: 300
    visible: true
    title: qsTr("PokeWiki")

    function changeGIF() {
        if (statsTable.name != "Pokemon not found :(") {
            animatedImage.source = "https://img.pokemondb.net/sprites/black-white/anim/normal/" + statsTable.name + ".gif";
        } else {
            animatedImage.source = "images/question.gif"
        }
    }


    Column {
        anchors.centerIn: parent

        AnimatedImage {
            id: animatedImage
            cache: true
            height: 100
            width: 200
            asynchronous: true
            fillMode: Image.Pad
            source: "images/pikachu.gif"

        }

        Text {
            width: 200
            text: statsTable.name
            font.family: "Helvetica"
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
        }
        Item {
            TableView {
                anchors.fill: parent
                columnSpacing: 0
                rowSpacing: 0
                clip: true

                model: CustomTableModel{
                    id: statsTable
                    name: "pikachu"
                    onNameChanged: changeGIF()
                }

                delegate: Rectangle {
                    implicitWidth: 98
                    implicitHeight: 40
                    border.width: 1

                    Text {
                        text: display
                        anchors.centerIn: parent
                    }
                }
            }
            height: 120
            width: 200
        }
        Item {
            height: 50
            width: 200
            Row {
                anchors.centerIn: parent
                TextField {
                    id: searchText
                    width: 100
                    height: 25
                    text: "pikachu"
                }
                Button {
                    width: 40
                    height: 25
                    icon.source: "images/search.svg"
                    icon.color: "transparent"
                    text: "Найти"
                    display: Button.IconOnly
                    onClicked: {
                        statsTable.onUpdate(searchText.text)
                    }
                }
            }
        }
    }



}
