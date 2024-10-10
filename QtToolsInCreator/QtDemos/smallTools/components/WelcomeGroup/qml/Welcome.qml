﻿import QtQuick 2.7
import QtQuick.Controls 1.4
import Welcome 1.0

Item {
    id: welcome
    width: 620
    height: 540

    WelcomeManage {
        id: welcomeManage
    }

    Text {
        x: 162
        y: 170
        text:
"欢迎使用JQTools，这是一个基于Qt开发的开源小工具包。
包含了在开发程序（尤其是Qt程序）时，需要的各种小功能。
本工具使用 QML(界面) 和 C++(逻辑) 开发，源码均已开源在了GitHub上。
若要浏览更详细的介绍，也可以前往GitHub"
        anchors.verticalCenterOffset: -68
        anchors.horizontalCenterOffset: 1
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Button {
        x: 254
        y: 278
        width: 120
        height: 40
        text: "前往Qt官方文档"
        anchors.verticalCenterOffset: 53
        anchors.horizontalCenterOffset: -95
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        onClicked: {
            welcomeManage.openGitHubLink();
        }
    }

    Button {
        x: 254
        y: 278
        width: 120
        height: 40
        text: "下载Qt中文文档pdf"
        anchors.verticalCenterOffset: 53
        anchors.horizontalCenterOffset: 95
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        onClicked: {
            welcomeManage.openLatestVersionDownloadLink();
        }
    }

    Text {
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 3
        text: "作者：BreakWorld    当前版本：V" + welcomeManage.jqToolsVersionString();
        verticalAlignment: Text.AlignBottom
        horizontalAlignment: Text.AlignRight
        color: "#a1a1a1"
    }
}
