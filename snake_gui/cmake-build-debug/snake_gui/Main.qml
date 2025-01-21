import QtQuick
import QtMultimedia 6.0

Window {
    width: 600
    height: 800
    visible: true
    title: qsTr("Snakes")

    FontLoader { id: fontLoader; source: "fonts/retro.ttf" }

    Image {
        anchors.fill: parent
        source: "images/background.png"
        fillMode: Image.Pad
    }

    Loader {
        z:2
        id: pageLoader
        anchors.fill: parent
        visible: true
        source: "./HomePage/HomePage.qml"

    }


    MediaPlayer {
        id: mediaPlayer
            source: "qrc:/snake_gui/sounds/song.mp3"  // Path to the music file
        audioOutput: AudioOutput {
            volume: 0.5
        }  // Required in Qt 6

    }
    Component.onCompleted: {
        mediaPlayer.play()
    }
}
