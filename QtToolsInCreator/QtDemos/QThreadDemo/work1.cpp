#include "work1.h"
#include <QThread>

Work1::Work1(QObject *parent) : QObject(parent)
{
    m_thread = new QThread;
    m_thread->start();
    this->moveToThread(m_thread);
    connect(this, &Work1::start, this, &Work1::threadfunction);




}

Work1::~Work1()
{
    m_thread->quit();           // 告诉线程的事件循环退出
    m_thread->wait();
}

void Work1::threadfunction()
{
    int val = 10;
    emit updataData(val);
    QThread::sleep(5);  // 延时5秒，模拟耗时操作
    emit updataData(100);
}
