#pragma once

#ifdef WIN32  
#pragma execution_character_set("utf-8")   //����utf-8�ַ��� ��ֹ��������
#endif

#include <QtWidgets/QMainWindow>
#include <QAction>
#include <QMenu>
#include <QString>
#include <QMap> 
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include "ui_GraphicsItem_test.h"


class GraphicsItem_test : public QMainWindow
{
    Q_OBJECT

public:
    GraphicsItem_test(QWidget *parent = Q_NULLPTR);

	//�˵��Ͷ�Ӧ�Ķ���
	void initActions();
	void initMenus();
	void initScene();
	void initView();
protected slots:
	void on_new_act();
	void on_clear_act();
	void on_eclipse_act();
	void on_polygon_act();
	void on_text_act();
	void on_rect_act();
	void on_alpha_act();
	void on_sunshine_act();
	void on_star_act();
private:
    Ui::GraphicsItem_testClass ui;

	QString strnew = "new";
	QString strclear = "clear";
	QString strclose = "close";
	QString strEclispe = tr("��Բ");
	QString strPolygon = tr("�����");
	QString strtext = tr("����");
	QString strRectangular = tr("������");
	QString strTransparency = tr("͸��ͼƬ");
	QString strSunshineCircle = tr("��˸Բ");
	QString strStar = tr("����");

	QMap<QString, QAction*> actions;

	//����
	QGraphicsScene *scene;
	//��ͼ
	QGraphicsView *view;
	
};
