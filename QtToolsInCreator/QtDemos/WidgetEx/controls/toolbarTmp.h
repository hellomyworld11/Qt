#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>

namespace Ui {
class toolbarTmp;
}

//标题工具栏
class toolbarTmp : public QWidget
{
    Q_OBJECT

public:
    explicit toolbarTmp(QWidget *parent = nullptr);
    ~toolbarTmp();

    QWidget* getBackground() const;
private:
    Ui::toolbarTmp *ui;
};

#endif // TOOLBAR_H
