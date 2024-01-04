#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->btn_testInter , &QPushButton::clicked, this,
            &Widget::on_btn_inter);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btn_inter()
{
   if(!proWidet)
   {
       proWidet = new NetProperty(this);
       proWidet->show();
   }
}

