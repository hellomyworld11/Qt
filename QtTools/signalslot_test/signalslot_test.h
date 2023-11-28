#pragma once

#include <QtWidgets/QMainWindow>
#include <QPushButton>
#include "ui_signalslot_test.h"

class signalslot_test : public QMainWindow
{
    Q_OBJECT

public:
    signalslot_test(QWidget *parent = Q_NULLPTR);

public slots:
	void on_btn1_clicked();
	void on_btn2_clicked();
private:
    Ui::signalslot_testClass ui;
};
