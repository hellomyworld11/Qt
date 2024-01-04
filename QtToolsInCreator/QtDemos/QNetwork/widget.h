#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "netproperty.h"

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
private:
    Ui::Widget *ui;

    NetProperty *proWidet;
};
#endif // WIDGET_H
