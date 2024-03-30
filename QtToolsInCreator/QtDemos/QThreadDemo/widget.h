#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QThread>
#include "mythread.h"

class Work1;
class Work2;


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:

    void getData(int data);
    void on_btn_threadInside_clicked();
    void on_btn_mythread_start();
    void on_btn_mythread_stop();
private:
    Ui::Widget *ui;

    MyThread* m_mythread = nullptr;

    Work1* m_newWork = nullptr;
    Work2* m_newWork2 = nullptr;
    QThread* m_thread = nullptr;

};
#endif // WIDGET_H
