#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtTools.h"

class QtTools : public QMainWindow
{
    Q_OBJECT

public:
    QtTools(QWidget *parent = Q_NULLPTR);

private:
    Ui::QtToolsClass ui;
};
