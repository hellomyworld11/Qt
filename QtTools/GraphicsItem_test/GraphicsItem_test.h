#pragma once

#include <QtWidgets/QMainWindow>
#include <QAction>
#include <QMenu>
#include <QString>
#include <QMap> 
#include "ui_GraphicsItem_test.h"


class GraphicsItem_test : public QMainWindow
{
    Q_OBJECT

public:
    GraphicsItem_test(QWidget *parent = Q_NULLPTR);

	//�˵��Ͷ�Ӧ�Ķ���
	void initActions();
	void initMenus();


private:
    Ui::GraphicsItem_testClass ui;
	QMap<QString, QAction*> actions;
};
