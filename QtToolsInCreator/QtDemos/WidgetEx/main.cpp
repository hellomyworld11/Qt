#include "widgetex.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WidgetEx w;
    w.show();
    return a.exec();
}
