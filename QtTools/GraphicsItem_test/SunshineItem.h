#ifndef SUNSHINEITEM_H_
#define SUNSHINEITEM_H_

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QTimer>

//自定义图元  变色的圆
class SunshineItem : public QObject,public QGraphicsItem
{
	Q_OBJECT
public:
	explicit SunshineItem(QObject *parent = 0);
	~SunshineItem();

	//必须实现的函数 定义包络
	QRectF boundingRect()const;
	//必须实现的函数 定义绘制
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);


	void timerEvent(QTimerEvent *ev);

private:
	QTimer *timer;
	bool   flash;
};











#endif