﻿import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2

Window {
    id: root
    property alias text: label.text
    signal clicked
    width: 116; height: 26
    color: "lightsteelblue"
//    border.color: "slategrey"
    Text {
        id: label
        anchors.centerIn: parent
        text: "Start"
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            root.clicked()
        }
    }
}
