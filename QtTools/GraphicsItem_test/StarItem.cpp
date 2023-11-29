#include "StarItem.h"



StarItem::StarItem()
{
	pix.load("shuaxin.ico");
}


QRectF StarItem::boundingRect() const
{
	return QRectF(-pix.width() / 2, -pix.height() / 2, pix.width(), pix.height());
}

void StarItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->drawPixmap(boundingRect().topLeft(), pix);
}

