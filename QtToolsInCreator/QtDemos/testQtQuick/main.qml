import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2


Window{
    visible: true
    Rectangle{
        width: 400
        height: 400
        color: "blue"
    }

    Image {
        id: name
        source: "res/鼠标.png"
        width: 100
        height: 100
        anchors.left: parent
    }

    Text {
        x:110
        y:0
        width: 100
        height: 90
        id: text1
        text: qsTr("text1")
    }

    Button{
        x:0
        y:100
        text: text1.text
    }
}
