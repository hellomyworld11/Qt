#include "netproperty.h"
#include "ui_netproperty.h"

#include <QNetworkInterface>
#include <QList>

NetProperty::NetProperty(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::NetProperty)
{
    ui->setupUi(this);

    this->setWindowTitle("获取网卡接口、IP地址");

    void (QComboBox::*fun)(int) = static_cast<void (QComboBox::*)(int)>(&QComboBox::activated);
    connect(ui->com_Interface, fun, this, &NetProperty::on_com_Interface_activated);

    // 表格自适应
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);                 // 设置如何将标题大小调整为给定模式所述大小的约束。
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);     // 然后设置要根据内容使用宽度的列

    Init();
}

NetProperty::~NetProperty()
{
    delete ui;
}

void NetProperty::on_com_Interface_activated(int index)
{
    Q_UNUSED(index) //取消警告
    QString strName = ui->com_Interface->currentData().toString();
    QNetworkInterface interface =  QNetworkInterface::interfaceFromName(strName);   // 根据选择名称获取网卡

    if(!interface.isValid())   // 判断接口有效
    {
        return;
    }

    ui->tableWidget->item(0, 1)->setText(QString::number(interface.index()));                     // 获取网卡索引
#if (QT_VERSION >= QT_VERSION_CHECK(5,11,0))        // qt5.11以后版本才有
    ui->tableWidget->item(1, 1)->setText(QString::number(interface.maximumTransmissionUnit()));   // 获取网卡最大传输数据单元
#endif
    ui->tableWidget->item(2, 1)->setText(interface.name());                                       // 获取网卡名称

#if 0    // 直接显示标志枚举
    QNetworkInterface::InterfaceFlags flags = interface.flags();
    QMetaEnum metaEnum = QMetaEnum::fromType<QNetworkInterface::InterfaceFlags>();
    ui->tableWidget->item(3, 1)->setText(metaEnum.valueToKeys(flags));                            // 返回与此网络接口关联的标志
#else
    ui->tableWidget->item(3, 1)->setText(FlagsToQString(interface.flags()));
#endif
#if (QT_VERSION >= QT_VERSION_CHECK(5,11,0))        // qt5.11以后版本才有
    ui->tableWidget->item(4, 1)->setText(TypeToQString(interface.type()));                        // 获取网络类型说明
#endif
    ui->tableWidget->item(5, 1)->setText(interface.hardwareAddress());                            // // 获取MAC地址

    ui->textEdit_ip->clear();
}

void NetProperty::Init()
{
    const QList<QNetworkInterface> qnetworkInters =  QNetworkInterface::allInterfaces();

    ui->com_Interface->clear();
    for(const QNetworkInterface& interface : qnetworkInters)
    {
        qDebug() << interface.humanReadableName();
        qDebug() << interface.name();
        ui->com_Interface->addItem(interface.humanReadableName(), interface.name());       // 显示所有网络接口名称
    }
}
