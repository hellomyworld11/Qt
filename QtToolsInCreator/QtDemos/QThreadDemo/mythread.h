#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>

//创建线程方式2 继承QThread 并重写run函数
class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);
    ~MyThread() override;

signals:
    void updateData(int num);

public slots:
    void abort();

protected:
    void run() override;

private:
    bool m_abort = false;
};

#endif // MYTHREAD_H
