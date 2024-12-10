import QtQuick 2.7
import MakeIcon 1.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2

Item {
    id:makeicon
    width: 620
    height: 540

    MakeIconManage{
        id:makeIconManage
    }

    MessageDialog{
        id: messagebox
        title: "警告"
        text: "默认消息"
        Component.onCompleted: visible = false
    }


    Item {
        id: centerItem
        anchors.centerIn: parent
        width:640
        height: 430

        //保存路径
        Text {
            id: targetSavePath
            x:49
            y:60
            width: 400
            text: qsTr("保存路径: ") + str_target_SavePath
            elide: Text.ElideLeft
            property string str_target_SavePath: iconMakerManage.targetSavePath()
        }
        //源路径
        Text {
            id: sourcePath
            x:49
            y:86
             width: 400
            text: qsTr("源路径: ") + str_sourcePath
            elide: Text.ElideLeft
            property string str_sourcePath: "未选择"
        }
        //原图宽
        Text {
            id: sourceIconImageWidht
            x: 49
            y: 112
            text: "原图宽：" + str_sourceIconImageWidht

            property string str_sourceIconImageWidht: "未选择"
        }

        Text {
            id: sourceIconImageHight
            x: 49
            y: 138
            text: "原图高：" + str_sourceIconImageHeight

            property string str_sourceIconImageHeight: "未选择"
        }

        Button{
            x:279
            y:208
            width:120
            height: 40
            text: "选择原图"
            background: Rectangle{
                        border.color: "royalblue"
                        border.width: 1
                        color: btn.down ? "red" : "lightsteelblue"
                    }

            onClicked: {
                var reply = makeIconManage.chooseSourceIconFilePath();
                console.log("choose")
                messagebox.visible = true;
                switch(reply)
                {
                case "cancel": messagebox.text = "用户取消操作"; break;
                case "OK": messagebox.text = "保存路径已更改";break;
                }
            }

        }

        Button{
            x:279
            y:291
            width:120
            height: 40
            text: "更改保存路径"

            onClicked: {


            }
        }

    }

}
