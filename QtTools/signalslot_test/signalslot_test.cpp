#include "signalslot_test.h"
#include <QDebug>

signalslot_test::signalslot_test(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	// ��ʽ1
	//connect(ui.btn_1, &QPushButton::clicked, this, &signalslot_test::on_btn1_clicked);
	//connect(ui.btn_2, &QPushButton::clicked, this, &signalslot_test::on_btn1_clicked);
	// ��ʽ2
	connect(ui.btn_1, SIGNAL(clicked()), this, SLOT(on_btn1_clicked()));
	connect(ui.btn_2, SIGNAL(clicked()), this, SLOT(on_btn2_clicked()));
}

void signalslot_test::on_btn1_clicked()
{
	qDebug() << "btn 1 clicked";
}

void signalslot_test::on_btn2_clicked()
{
	qDebug() << "btn 2 clicked";
}
