import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2

Window {
    visible: true
    width: 360
    height: 360
    Text {
        x: wid
        anchors.centerIn: parent
        text: "Hello World"
        color: "red"
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    Button {
        anchors.centerIn: parent
        text: "Ok"
        onClicked: {
            console.log("button click");
        }
    }
}
