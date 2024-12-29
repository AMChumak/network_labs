import QtQuick

Window {
    width: 1000
    height: 600
    visible: true
    title: qsTr("Hello World")

    Loader {
        id: pageLoader
        anchors.fill: parent
        source: "SessionPage.qml"
    }
}
