#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "netproperty.h"
#include "tcpserver.h"
#include "tcpclient.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
    void  on_btn_inter();
    void on_btn_tcpServer();
    void on_btn_tcpClient();
private:
    Ui::Widget *ui;

    NetProperty *proWidet = nullptr;
    TcpServer *tcpserver = nullptr;
    TcpClient *tcpClient = nullptr;
};
#endif // WIDGET_H
