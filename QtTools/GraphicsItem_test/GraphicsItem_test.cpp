#include "GraphicsItem_test.h"
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include "SunshineItem.h"
#include "StarItem.h"

GraphicsItem_test::GraphicsItem_test(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	initActions();
	initMenus();

	initScene();	
	initView();
	setCentralWidget(view);

	resize(550, 450);
	setWindowTitle(tr("Graphics Items"));
}

void GraphicsItem_test::initActions()
{
	QAction *newAct = new QAction(strnew, this);
	QAction *clearAct = new QAction(strclear, this);
	QAction *closeAct = new QAction(strclose, this);
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

	connect(newAct, &QAction::triggered, this, &GraphicsItem_test::on_new_act);
	connect(clearAct, &QAction::triggered, this, &GraphicsItem_test::on_clear_act);
	connect(closeAct, &QAction::triggered, this, &GraphicsItem_test::close);
	connect(addEclipse, &QAction::triggered, this, &GraphicsItem_test::on_eclipse_act);
	connect(addPolygon, &QAction::triggered, this, &GraphicsItem_test::on_polygon_act);
	connect(addtext, &QAction::triggered, this, &GraphicsItem_test::on_text_act);
	connect(addRectangular, &QAction::triggered, this, &GraphicsItem_test::on_rect_act);
	connect(addTransparency, &QAction::triggered, this, &GraphicsItem_test::on_alpha_act);
	connect(addSunshineCircle, &QAction::triggered, this, &GraphicsItem_test::on_sunshine_act);
	connect(addStar, &QAction::triggered, this, &GraphicsItem_test::on_star_act);
}

void GraphicsItem_test::initMenus()
{
	QMenu *fileMenu = menuBar()->addMenu(tr("文件"));
	QMenu *editMenu = menuBar()->addMenu(tr("编辑"));

	fileMenu->addAction(actions[strnew]);
	fileMenu->addAction(actions[strclear]);
	fileMenu->addAction(actions[strclose]);

	editMenu->addAction(actions[strEclispe]);
	editMenu->addAction(actions[strPolygon]);
	editMenu->addAction(actions[strtext]);
	editMenu->addAction(actions[strRectangular]);
	editMenu->addAction(actions[strTransparency]);
	editMenu->addAction(actions[strSunshineCircle]);
	editMenu->addAction(actions[strStar]);
}

void GraphicsItem_test::initScene()
{
	scene = new QGraphicsScene;
	scene->setSceneRect(-200, -200, 400, 400);
}

void GraphicsItem_test::initView()
{
	view = new QGraphicsView;
	view->setScene(scene);
	view->setMinimumSize(400, 400);
	view->show();
}

void GraphicsItem_test::on_new_act()
{

}

void GraphicsItem_test::on_clear_act()
{

}

void GraphicsItem_test::on_eclipse_act()
{
	QGraphicsEllipseItem *item = new QGraphicsEllipseItem(QRectF(0, 0, 80, 60));
	item->setPen(Qt::NoPen);
	item->setBrush(QColor(qrand() % 256, qrand() % 256, qrand() % 256));
	item->setFlag(QGraphicsItem::ItemIsMovable);

	scene->addItem(item);
	item->setPos((qrand() % int(scene->sceneRect().width())) - 200, (qrand() % int(scene->sceneRect().height())) - 200);
}

void GraphicsItem_test::on_polygon_act()
{
	
}

void GraphicsItem_test::on_text_act()
{
	QGraphicsTextItem *item = new QGraphicsTextItem;
	item->setPlainText("hello world");
	QFont font("Times", 16);
	item->setFont(font);
	scene->addItem(item);
	item->setFlag(QGraphicsItem::ItemIsMovable);
	item->setDefaultTextColor(QColor(qrand() % 256, qrand() % 256, qrand() % 256));
	item->setPos((qrand() % int(scene->sceneRect().width())) - 200, (qrand() % int(scene->sceneRect().height())) - 200);
}

void GraphicsItem_test::on_rect_act()
{
	//TODO
}

void GraphicsItem_test::on_alpha_act()
{
	QGraphicsPixmapItem *item = scene->addPixmap(QPixmap("a.png"));
	item->setFlag(QGraphicsItem::ItemIsMovable);
	item->setPos((qrand() % int(scene->sceneRect().width())) - 200, (qrand() % int(scene->sceneRect().height())) - 200);
}

void GraphicsItem_test::on_sunshine_act()
{
	SunshineItem *item = new SunshineItem;
	scene->addItem(item);
	item->setPos((qrand() % int(scene->sceneRect().width())) - 200, (qrand() % int(scene->sceneRect().height())) - 200);
}

void GraphicsItem_test::on_star_act()
{
	StarItem *item = new StarItem;
	//动画
	QGraphicsItemAnimation *anim = new QGraphicsItemAnimation;
	anim->setItem(item);
	//时间线
	QTimeLine *timeLine = new QTimeLine(4000);
	timeLine->setCurveShape(QTimeLine::SineCurve);
	timeLine->setLoopCount(0);

	anim->setTimeLine(timeLine);

	int y = (qrand() % 400) - 200;
	for (int i = 0; i < 400; i++)
	{
		anim->setPosAt(i / 400.0, QPointF(i - 200, y));
	}
	timeLine->start();
	scene->addItem(item);

}
