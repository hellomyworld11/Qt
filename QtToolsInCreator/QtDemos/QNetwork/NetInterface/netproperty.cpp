#include "netproperty.h"
#include "ui_netproperty.h"

NetProperty::NetProperty(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::NetProperty)
{
    ui->setupUi(this);

    connect(ui->com_Interface, &QComboBox::activated, this, &NetProperty::on_com_Interface_activated);
}

NetProperty::~NetProperty()
{
    delete ui;
}

void NetProperty::on_com_Interface_activated(int index)
{
}
