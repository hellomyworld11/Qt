#include "QUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QUI w;
    w.show();
    return a.exec();
}
