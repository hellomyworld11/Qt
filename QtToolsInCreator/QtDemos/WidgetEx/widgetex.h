#ifndef WIDGETEX_H
#define WIDGETEX_H

#include <QWidget>
#include "widgettemp.h"

QT_BEGIN_NAMESPACE
namespace Ui { class WidgetEx; }
QT_END_NAMESPACE

class WidgetEx : public WidgetTemp
{
    Q_OBJECT

public:
    WidgetEx(QWidget *parent = nullptr);
    ~WidgetEx();

private:
    void init();
    void connectSlot();
    void loadStyle();
    void setWindowTitle(const QString & title);

private:
    Ui::WidgetEx *ui;
};
#endif // WIDGETEX_H
