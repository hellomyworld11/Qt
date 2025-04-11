#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPainter>
#include <QtMath>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , paintnum(0)
{
    ui->setupUi(this);

    setWindowTitle("仪表盘");
    setFixedSize(1280, 800);
    setStyleSheet("#MainWindow{background-image:url(:/res/img/background.png)}");

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::slot_speed_changed);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Space) {
        if (!bSpeed) {
            bSpeed = true;
            timer->start();
        }
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Space) {
        bSpeed = false;
    }
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    qDebug() << "paintEvent ... " << paintnum++;

    //绘制仪表盘主体背景
    QPainter painter(this);
    int width = this->width();
    int height = this->height() - 100;
    int radius = height / 2.0;

    qDebug() << "height " << height;
    //移到中心位置

    painter.translate(width / 2, height * 0.6);
    //反锯齿
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    //设置画刷颜色
    painter.setBrush(QColor(138, 43, 226));
    //绘制刻度线
    drawScaleLine(painter, radius - 60);
    //绘制刻度值
    drawScaleValue(painter, radius - 90);
    //外扇形
    drawCicle(painter, radius - 35);
    //进度扇形
    drawProgressCicle(painter, radius - 35);
    //绘制指针
    drawPointer(painter, radius - 140);
    //绘制中心圆
    drawCenterCircle(painter, radius - 150);

    //绘制时速
    drawSpeedTxt(painter, radius - 300);
}

void MainWindow::drawScaleLine(QPainter& painter, int radius)
{
    //组装点的路径图
    QPainterPath pointPath_small;
    pointPath_small.moveTo(-2, -2);
    pointPath_small.lineTo(2, -2);
    pointPath_small.lineTo(2, 8);
    pointPath_small.lineTo(-2, 8);
    //  painter.drawPath(pointPath_small);

    QPainterPath pointPath_big;
    pointPath_big.moveTo(-2, -2);
    pointPath_big.lineTo(2, -2);
    pointPath_big.lineTo(2, 20);
    pointPath_big.lineTo(-2, 20);
    // painter.drawPath(pointPath_big);

    //绘制121个小点
    for (int i = 0; i < 121; i += 2) {
        QPointF point(0, 0);
        painter.save();
        point.setX(radius * qCos(((210 - i * 2) * M_PI) / 180));
        point.setY(radius * qSin(((210 - i * 2) * M_PI) / 180));
        painter.translate(point.x(), -point.y());

        painter.rotate(-120 + i * 2);

        if (i < 80) {
            painter.setBrush(QColor(255, 255, 255));
        }
        if (i >= 80) {
            painter.setBrush(QColor(235, 70, 70));
        }

        if (i % 5 == 0) {
            painter.drawPath(pointPath_big); //绘画大刻度
        } else {
            painter.drawPath(pointPath_small); //绘画小刻度
        }
        painter.restore();
    }
}

void MainWindow::drawScaleValue(QPainter& painter, int radius)
{
    painter.setPen(QColor(255, 255, 255));
    QFont font;
    font.setFamily("Arial");
    font.setPointSize(15);
    font.setBold(true);
    painter.setFont(font);
    QString value;
    for (int i = 0; i < 13; i++) {
        QPointF point(0, 0);
        painter.save();

        int angle = (210 - i * 20);

        qreal x = radius * qCos(angle * M_PI / 180);
        qreal y = radius * qSin(angle * M_PI / 180);

        point.setX(x);
        point.setY(y);
        value = QString::number(i * 20);
        painter.translate(x, -y);
        painter.rotate(-120 + i * 20);
        painter.drawText(-25, 0, 50, 20, Qt::AlignHCenter, value);
        painter.restore();
    }
}

void MainWindow::drawCicle(QPainter& painter, int radius)
{
    painter.save();
    //计算大小圆路径
    painter.setPen(Qt::NoPen);
    QPainterPath outRing;
    QPainterPath inRing;
    outRing.moveTo(0, 0);
    inRing.moveTo(0, 0);
    outRing.arcTo(-radius, -radius, 2 * radius, 2 * radius, -30, 240);
    inRing.addEllipse(-radius + 50, -radius + 50, 2 * (radius - 50), 2 * (radius - 50));
    outRing.closeSubpath();
    //设置渐变色k
    QRadialGradient radialGradient(0, 0, radius, 0, 0);
    radialGradient.setColorAt(1, QColor(0, 82, 199));
    radialGradient.setColorAt(0.92, Qt::transparent);
    //设置画刷
    painter.setBrush(radialGradient);
    painter.drawPath(outRing.subtracted(inRing));
    painter.restore();
}

void MainWindow::drawProgressCicle(QPainter& painter, int radius)
{
    QRect rect(-radius, -radius, 2 * radius, 2 * radius);
    QConicalGradient Conical(0, 0, -70);

    Conical.setColorAt(0.1, QColor(255, 88, 127, 200)); //红色
    Conical.setColorAt(0.5, QColor(53, 179, 251, 150)); //蓝色
    painter.setBrush(Conical);
    painter.drawPie(rect, 210 * 16, -(pos)*16);
}

void MainWindow::drawPointer(QPainter& painter, int radius)
{
    //指针
    QPainterPath path;
    path.moveTo(10, 0);
    path.lineTo(1, -radius);
    path.lineTo(-1, -radius);
    path.lineTo(-10, 0);
    path.arcTo(-10, 0, 20, 20, 180, 180);

    QPainterPath inRing;
    inRing.addEllipse(-5, -5, 10, 10);

    painter.save();
    painter.setBrush(QColor(255, 255, 255));
    painter.rotate(pos - 120);
    // painter.drawPath(path);
    painter.drawPath(path.subtracted(inRing));
    painter.restore();
}

void MainWindow::drawCenterCircle(QPainter& painter, int radius)
{
    //保存绘图对象
    painter.save();
    painter.setPen(Qt::NoPen);
    //计算大小圆路径
    QPainterPath inRing;
    inRing.moveTo(0, 0);
    inRing.addEllipse(-radius + 50, -radius + 50, 2 * (radius - 50), 2 * (radius - 50));
    //设置画刷
    painter.setBrush(QColor(10, 20, 30));
    painter.drawPath(inRing);
    painter.restore();

    int shinerad = radius - 80;
    painter.save();
    painter.setPen(Qt::NoPen);
    QRadialGradient radialGradient(0, 0, shinerad, 0, 0);
    //    radialGradient.setColorAt(0.5,QColor(8,77,197));
    radialGradient.setColorAt(0.5, QColor(10, 68, 185, 150));
    radialGradient.setColorAt(1.0, Qt::transparent);
    painter.setBrush(QBrush(radialGradient));
    painter.drawRect(-shinerad, -shinerad, 2 * (shinerad), 2 * (shinerad));
    painter.restore();

    int littleRad = radius - 50;
    //保存绘图对象
    painter.save();
    painter.setPen(Qt::NoPen);
    //计算大小圆路径
    QPainterPath inRing_little;
    inRing.moveTo(0, 0);
    inRing.addEllipse(-littleRad + 50, -littleRad + 50, 2 * (littleRad - 50), 2 * (littleRad - 50));
    //设置画刷
    painter.setBrush(QColor(10, 20, 30));
    painter.drawPath(inRing_little);

    painter.restore();
}

void MainWindow::drawSpeedTxt(QPainter& painter, int radius)
{
    painter.save();
    painter.setPen(QColor(255, 255, 255));
    QFont font;
    font.setFamily("Arial");
    font.setPointSize(15);
    painter.setFont(font);
    QString speed = QString::number(pos) + "km/h";
    painter.drawText(-75, -radius - 20, 150, 100, Qt::AlignCenter, speed);
    painter.restore();
}

void MainWindow::slot_speed_changed()
{
    if (bSpeed) {
        if (pos < 240) {
            pos++;
        }
    } else {
        if (pos == 0) {
            timer->stop();
        }
        if (pos > 0) {
            pos--;
        }
    }
    update();
}
