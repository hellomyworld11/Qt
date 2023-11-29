#include "SunshineItem.h"



SunshineItem::SunshineItem(QObject *parent):QObject(parent)
{
	flash = true;
	setFlag(ItemIsMovable);
	startTimer(1000);
}


SunshineItem::~SunshineItem()
{
}

QRectF SunshineItem::boundingRect() const
{
	qreal adjust = 2;
	return QRectF(-10 - adjust, -10 - adjust, 43 + adjust, 43 + adjust);
}

void SunshineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /*= Q_NULLPTR*/)
{
	painter->setPen(Qt::NoPen);
	painter->setBrush(Qt::darkGray);
	painter->drawEllipse(-7, -7, 40, 40);

	painter->setPen(QPen(Qt::black, 0));
	painter->setBrush(flash ? (Qt::red) : (Qt::yellow));
	painter->drawEllipse(-10, -10, 40, 40);
}

void SunshineItem::timerEvent(QTimerEvent *ev)
{
	flash = !flash;
	update();
}
