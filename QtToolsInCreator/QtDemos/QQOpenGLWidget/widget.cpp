#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    Init();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::Init()
{
    // 使用QOpenGLWindow绘制
    m_openglWindow = new OpenGlWindow;
    ui->gridLayout->addWidget(QWidget::createWindowContainer(m_openglWindow));

    initConnect();
}

void Widget::initConnect()
{
    connect(ui->btn_draw, &QPushButton::clicked, this, &Widget::on_btn_drawTangle);
    connect(ui->btn_rotate, &QPushButton::clicked, this, &Widget::on_btn_rotate);
    connect(ui->btn_loadobj, &QPushButton::clicked, this, &Widget::on_btn_loadObj);
    connect(ui->btn_cube, &QPushButton::clicked, this, &Widget::on_btn_cube);
}

void Widget::on_btn_drawTangle()
{
    if(m_openglWindow)
    {
        m_openglWindow->DrwTrangle(true);
        m_openglWindow->update();
    }
}

void Widget::on_btn_rotate()
{
    if(m_openglWindow)
    {
        angle+=30;
        m_openglWindow->SetTrangleAngle(angle%360);
        m_openglWindow->update();
    }
}

void Widget::on_btn_loadObj()
{
    if(m_openglWindow)
    {

    }
}

void Widget::on_btn_cube()
{
    if(m_openglWindow)
    {
        m_openglWindow->DrwCube(true);
        m_openglWindow->update();
    }
}

