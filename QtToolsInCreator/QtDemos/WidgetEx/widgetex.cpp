#include "widgetex.h"
#include "ui_widgetex.h"
#include <QFile>
#include <QIODevice>

WidgetEx::WidgetEx(QWidget* parent)
    : WidgetTemp(parent)
    , ui(new Ui::WidgetEx)
{
    ui->setupUi(this);
}

WidgetEx::~WidgetEx()
{
    delete ui;
}

void WidgetEx::init()
{
    loadStyle();
    this->setWindowTitle(QString("自定义窗口 - V%1").arg("1.0"));
    this->setToolBar(ui->toolbar->getBackground()); // 设置标题栏
}

void WidgetEx::loadStyle()
{
    QFile styleFile(":/Style/style.css");
    if (!styleFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QString stylestr = styleFile.readAll();
    qApp->setStyleSheet(stylestr);
}

void WidgetEx::setWindowTitle(const QString& title)
{
    QWidget::setWindowTitle(title);
    ui->toolbar->setWindowTitle(title);
}
