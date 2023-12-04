#include "widgetex.h"
#include "ui_widgetex.h"

WidgetEx::WidgetEx(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetEx)
{
    ui->setupUi(this);
}

WidgetEx::~WidgetEx()
{
    delete ui;
}

