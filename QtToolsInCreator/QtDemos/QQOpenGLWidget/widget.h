#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "openglwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);

    ~Widget();
public:
    void Init();

    void initConnect();

protected slots:

    void on_btn_drawTangle();

    void on_btn_rotate();

    void on_btn_loadObj();

    void on_btn_cube();
private:
    Ui::Widget *ui;

    int angle = 0;
    OpenGlWindow *m_openglWindow = nullptr;
};
#endif // WIDGET_H
