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
}

MainWindow::~MainWindow()
{
    delete ui;
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
    drawScaleValue(painter, radius - 80);
    //绘制中心圆

    //绘制指针

    //绘制时速
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
