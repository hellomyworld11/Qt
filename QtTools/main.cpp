#include "QtTools.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtTools w;
    w.show();
    return a.exec();
}
