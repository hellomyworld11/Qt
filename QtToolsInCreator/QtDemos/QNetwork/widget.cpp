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
    connect(ui->btn_TcpServer , &QPushButton::clicked, this,
            &Widget::on_btn_tcpServer);
    connect(ui->btn_client , &QPushButton::clicked, this,
            &Widget::on_btn_tcpClient);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btn_inter()
{
   if(!proWidet)
   {
       proWidet = new NetProperty();
   }
   proWidet->show();
}

void Widget::on_btn_tcpServer()
{
    if(!tcpserver)
    {
        tcpserver = new TcpServer();
    }
    tcpserver->show();
}

void Widget::on_btn_tcpClient()
{
    if(!tcpClient)
    {
        tcpClient = new TcpClient();
    }
    tcpClient->show();
}

