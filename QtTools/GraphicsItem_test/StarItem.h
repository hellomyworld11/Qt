#ifndef  STARITEM_H_
#define  STARITEM_H_

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>


class StarItem : public QGraphicsItem
{
public:
	StarItem();

	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
	QPixmap pix;
};

#endif // _DEBUG