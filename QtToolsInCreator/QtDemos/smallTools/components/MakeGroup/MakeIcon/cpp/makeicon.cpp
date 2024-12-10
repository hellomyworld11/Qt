#include "makeicon.h"
#include <QFileDialog>
#include <QStandardPaths>

using namespace MakeIcon;

Manage::Manage()
{
}

QString Manage::chooseSourceIconFilePath()
{
    //    const auto&& sourceIconFilePath = QFileDialog::getOpenFileName(
    //        nullptr,
    //        "choose src img",
    //        QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
    //        "*.png *.jpg *.jpeg *.bmp");

    const auto&& sourceIconFilePath = QFileDialog::getOpenFileName(
        nullptr,
        "\u8BF7\u9009\u62E9\u56FE\u6807\u6587\u4EF6",
        QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
        "*.png *.jpg *.jpeg *.bmp");

    if (sourceIconFilePath.isEmpty())
        return "cancel";

    QImage srcIconImg;
    if (!srcIconImg.load(sourceIconFilePath))
        return "openFail";

    sourceIconFilePath_ = sourceIconFilePath;
    sourceIconImage_ = srcIconImg;

    emit sourceIconFilePathChanged();
    return "OK";
}
