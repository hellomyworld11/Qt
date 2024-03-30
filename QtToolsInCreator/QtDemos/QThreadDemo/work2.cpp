#include "work2.h"
#include <QThread>

Work2::Work2(QObject *parent) : QObject(parent)
{
    connect(this, &Work2::start, this, &Work2::threadfunction);
}

void Work2::threadfunction()
{
    emit updataData(10);
    QThread::sleep(5);  // 延时5秒，模拟耗时操作
    emit updataData(100);
}
