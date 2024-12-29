import QtQuick
import QtQuick.Controls

Rectangle{
    Column {
        id: mainSpacesColumn
        anchors.fill: parent

        Rectangle {
            id: header
            height:160
            width: parent.width

            Button {
                id: closeBtn
                height: 60;
                width: 60
                anchors.verticalCenter: parent.verticalCenter
                x: parent.x + 60
            }

            Image {
                source: "./images/snakes_game_title.png"
                height: parent.height
                width: 1.8 * height
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }
        }



    }

}
