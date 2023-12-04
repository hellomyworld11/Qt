#ifndef WIDGETEX_H
#define WIDGETEX_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class WidgetEx; }
QT_END_NAMESPACE

class WidgetEx : public QWidget
{
    Q_OBJECT

public:
    WidgetEx(QWidget *parent = nullptr);
    ~WidgetEx();

private:
    Ui::WidgetEx *ui;
};
#endif // WIDGETEX_H
