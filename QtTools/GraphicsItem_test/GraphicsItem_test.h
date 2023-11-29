#pragma once

#ifdef WIN32  
#pragma execution_character_set("utf-8")   //设置utf-8字符集 防止中文乱码
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

	//菜单和对应的动作
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
	QString strEclispe = tr("椭圆");
	QString strPolygon = tr("多边形");
	QString strtext = tr("文字");
	QString strRectangular = tr("长方形");
	QString strTransparency = tr("透明图片");
	QString strSunshineCircle = tr("闪烁圆");
	QString strStar = tr("星星");

	QMap<QString, QAction*> actions;

	//场景
	QGraphicsScene *scene;
	//视图
	QGraphicsView *view;
	
};
