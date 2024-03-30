#include "widget.h"
#include "ui_widget.h"
#include "work1.h"
#include "work2.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->lcdNumber->setDecMode();

    connect(ui->btn_threadInside, &QPushButton::clicked,
            this, &Widget::on_btn_threadInside_clicked);

    connect(ui->btn_st, &QPushButton::clicked,
            this, &Widget::on_btn_mythread_start);

    connect(ui->btn_ed, &QPushButton::clicked,
            this, &Widget::on_btn_mythread_stop);

    m_newWork = new Work1;
  //  connect(m_newWork, &Work1::updataData, ui->lcdNumber, QOverload<int>::of(&QLCDNumber::display));
    //ui->lcdNumber->display(10);

    m_thread = new QThread;
    m_newWork2 = new Work2;
    m_newWork2->moveToThread(m_thread);
    m_thread->start();
    connect(m_thread, &QThread::finished, m_newWork2, &QObject::deleteLater);
  //  connect(m_newWork2, &Work2::updataData, ui->lcdNumber, QOverload<int>::of(&QLCDNumber::display));

    m_mythread = new MyThread(this);
    connect(m_mythread, &MyThread::updateData, ui->lcdNumber, QOverload<int>::of(&QLCDNumber::display));

}

Widget::~Widget()
{
    if(m_newWork)
    {
        delete m_newWork;
    }
    m_thread->quit();
    m_thread->wait();
    delete m_thread;          // 由于m_thread没有指定父对象，所以需要自己释放
    m_thread = nullptr;
    delete ui;
}

void Widget::getData(int data)
{
    ui->lcdNumber->display(data);
}




void Widget::on_btn_threadInside_clicked()
{
    m_newWork->start();
}

void Widget::on_btn_mythread_start()
{
    m_mythread->start();
}

void Widget::on_btn_mythread_stop()
{
    m_mythread->abort();
}
