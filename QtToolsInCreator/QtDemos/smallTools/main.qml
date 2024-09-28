import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtGraphicalEffects 1.0
import Qt3D.Render 2.0

ApplicationWindow {
    id:applicationWindow
    visible: true
    width: 800
    height: 600
    title: qsTr("smalltools")
    color: "#FAFAFA"

    minimumWidth: 800
    minimumHeight: 600
//左上角矩形
    Rectangle{
        x: 0
        y: 0
        z: 1
        width: 180
        height: 64
        Text {
               width: parent.width
               height: parent.height
               text: qsTr("SmallTools")
               font.pointSize: 20
               verticalAlignment: Text.AlignVCenter
               horizontalAlignment: Text.AlignHCenter
               color: "#757575"
           }
    }
//右上角矩形区域
    RectangularGlow{
        x:180
        z:-1
        width:parent.width - 180
        height:64
        glowRadius: 5
        spread: 0.22
        color: "#30000000"
        cornerRadius: 3
    }
//竖线
    Rectangle {
        x: 180
        y: 0
        z: 1
        width: 1
        height: parent.height
        color: "#dcdcdc"
    }
//横线
    Rectangle {
        x: 0
        y: 63
        z: 1
        width: 180
        height: 1
        color: "#e1e1e1"
    }


}
