#ifndef NETPROPERTY_H
#define NETPROPERTY_H

#include <QWidget>

namespace Ui {
class NetProperty;
}

class NetProperty : public QWidget {
    Q_OBJECT

public:
    explicit NetProperty(QWidget* parent = nullptr);
    ~NetProperty();
private slots:
    void on_com_Interface_activated(int index);

private:
    void init();
    QString FlagsToQString(int flags);
    QString TypeToQString(int type);

private:
    Ui::NetProperty* ui;
};

#endif // NETPROPERTY_H
