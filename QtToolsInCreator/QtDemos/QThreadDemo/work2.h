#ifndef WORK2_H
#define WORK2_H

#include <QObject>

//创建线程方式1.2 work 放入线程 外部实现
class Work2 : public QObject
{
    Q_OBJECT
public:
    explicit Work2(QObject *parent = nullptr);

signals:
    void start();
    void updataData(int data);
public slots:
    void threadfunction();
};

#endif // WORK2_H
