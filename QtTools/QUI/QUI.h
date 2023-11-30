#pragma once

#include <QtWidgets/QDialog>
#include "ui_QUI.h"

class QUI : public QDialog
{
    Q_OBJECT

public:
    QUI(QWidget *parent = Q_NULLPTR);

private:
    Ui::QUIClass ui;
};
