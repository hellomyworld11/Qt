#include "widget.h"

#include <QApplication>
#include <QTreeView>
#include <QFile>
#include <QTextStream>
#include "treemodel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Widget w;
    // w.show();
    QFile file("I:\\learnPro\\QtPro\\Qt\\QtToolsInCreator\\QtDemos\\"
        "ModelViewDemo\\default.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return -1;

    QTextStream in(&file);
    QString str = in.readAll();

    TreeModel model(str);
    file.close();


    QTreeView view;
    view.setModel(&model);
    view.show();
    return a.exec();
}
