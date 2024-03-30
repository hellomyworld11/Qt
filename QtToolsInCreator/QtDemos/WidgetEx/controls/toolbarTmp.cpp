#include "toolbarTmp.h"
#include "ui_toolbarTmp.h"

toolbarTmp::toolbarTmp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::toolbarTmp)
{
    ui->setupUi(this);
}

toolbarTmp::~toolbarTmp()
{
    delete ui;
}

QWidget *toolbarTmp::getBackground() const
{
    return ui->background;
}
