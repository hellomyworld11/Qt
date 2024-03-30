#ifndef WORK1_H
#define WORK1_H

#include <QObject>

//创建线程方式1.1 work 放入线程 内部实现
class Work1 : public QObject
{
    Q_OBJECT
public:
    explicit Work1(QObject *parent = nullptr);
    ~Work1();
signals:
    void start();
    void updataData(int data);
public slots:
    void threadfunction();
private:
    QThread* m_thread;
};

#endif // WORK1_H
