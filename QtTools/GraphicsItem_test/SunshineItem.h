#ifndef SUNSHINEITEM_H_
#define SUNSHINEITEM_H_

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QTimer>

//�Զ���ͼԪ  ��ɫ��Բ
class SunshineItem : public QObject,public QGraphicsItem
{
	Q_OBJECT
public:
	explicit SunshineItem(QObject *parent = 0);
	~SunshineItem();

	//����ʵ�ֵĺ��� �������
	QRectF boundingRect()const;
	//����ʵ�ֵĺ��� �������
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);


	void timerEvent(QTimerEvent *ev);

private:
	QTimer *timer;
	bool   flash;
};











#endif