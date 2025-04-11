#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent* event);

    void keyReleaseEvent(QKeyEvent* event);

    void paintEvent(QPaintEvent* event);

    void drawScaleLine(QPainter& painter, int radius);

    void drawScaleValue(QPainter& painter, int radius);

    void drawCicle(QPainter& painter, int radius);

    void drawProgressCicle(QPainter& painter, int radius);

    void drawPointer(QPainter& painter, int radius);

    void drawCenterCircle(QPainter& painter, int radius);

    void drawSpeedTxt(QPainter& painter, int radius);
private slots:
    void slot_speed_changed();

private:
    Ui::MainWindow* ui;

    QTimer* timer;

    int paintnum;

    bool bSpeed = false;

    double pos = 0;
};
#endif // MAINWINDOW_H
