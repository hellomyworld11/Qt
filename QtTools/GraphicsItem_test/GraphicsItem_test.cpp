#include "GraphicsItem_test.h"


GraphicsItem_test::GraphicsItem_test(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);


	initActions();
	initMenus();
	
}

void GraphicsItem_test::initActions()
{
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


	QAction *newAct = new QAction("new", this);
	QAction *clearAct = new QAction("clear", this);
	QAction *closeAct = new QAction("close", this);
	QAction *addEclipse = new QAction(strEclispe, this);
	QAction *addPolygon = new QAction(strPolygon, this);
	QAction *addtext = new QAction(strtext, this);
	QAction *addRectangular = new QAction(strRectangular, this);
	QAction *addTransparency = new QAction(strTransparency, this);
	QAction *addSunshineCircle = new QAction(strSunshineCircle, this);
	QAction *addStar = new QAction(strStar, this);

	actions.insert(strnew, newAct);
	actions.insert(strclear, clearAct);
	actions.insert(strclose, closeAct);
	actions.insert(strEclispe, addEclipse);
	actions.insert(strPolygon, addPolygon);
	actions.insert(strtext, addtext);
	actions.insert(strRectangular, addRectangular);
	actions.insert(strTransparency, addTransparency);
	actions.insert(strSunshineCircle, addSunshineCircle);
	actions.insert(strStar, addStar);
}

void GraphicsItem_test::initMenus()
{
	QMenu *fileMenu = menuBar()->addMenu(tr("文件"));
	//fileMenu->addAction(actions[""]);
}
