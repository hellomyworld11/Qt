#include "tcpserver.h"
#include "ui_tcpserver.h"

TcpServer::TcpServer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TcpServer)
{
    ui->setupUi(this);

    setWindowTitle("Tcp服务器");

    init();

    connectSlots();
}

TcpServer::~TcpServer()
{
    delete ui;
}

void TcpServer::init()
{
    m_pTcpServer = new QTcpServer(this);
    m_pTcpServer->setMaxPendingConnections(30);
    ui->line_localAddress->setText("127.0.0.1");
}

void TcpServer::connectSlots()
{
    connect(m_pTcpServer, &QTcpServer::newConnection, this, &TcpServer::on_newConnection);    // 监听新的客户端连接
    connect(m_pTcpServer, &QTcpServer::acceptError, this, &TcpServer::on_acceptError);        // 当接受新连接导致错误时，会发出此信号

    connect(ui->but_connect, &QPushButton::clicked, this, &TcpServer::on_btn_listen);
    connect(ui->but_send, &QPushButton::clicked, this, &TcpServer::on_btn_send);
    connect(ui->but_clearRecv, &QPushButton::clicked, this, &TcpServer::on_btn_clearRev);
    connect(ui->but_clearSend, &QPushButton::clicked, this, &TcpServer::on_btn_clearSend);
    connect(ui->check_hexRecv, &QCheckBox::clicked, this, &TcpServer::on_check_hexRev);
    connect(ui->check_hexSend, &QCheckBox::clicked, this, &TcpServer::on_check_hexSend);
}

void TcpServer::addPeer(const QString &peer)
{
    QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
    QCheckBox* checkbox = new QCheckBox();          // 添加复选框
    checkbox->setText(peer);
    //设置item的高度
    item->setSizeHint(QSize(0,20));
    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item, checkbox);
}

qint64 TcpServer::sendData(const QByteArray &data)
{
    qint64 len = 0;
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        QCheckBox* checkBox = (QCheckBox*)ui->listWidget->itemWidget(ui->listWidget->item(i));
        if(checkBox->isChecked())                                      // 勾选的已连接Client则显示接收的信息
        {
             qint64 ret = connects.at(i)->write(data);
             if(ret > len)
             {
                 len = ret;
             }
        }
    }
    return len;
}

void TcpServer::on_newConnection()
{
    while (m_pTcpServer->hasPendingConnections())
    {
        QTcpSocket* tcpSocket = m_pTcpServer->nextPendingConnection();      // 存在内存泄漏，最好使用时通过hasPendingConnections判断是否有未返回的连接
        if(tcpSocket)
        {
            connects.append(tcpSocket);
        }
        connect(tcpSocket, &QTcpSocket::disconnected, this, &TcpServer::on_disconnected);        // 断开连接
        connect(tcpSocket, &QTcpSocket::readyRead, this, &TcpServer::on_readyRead);

        QString strPeer = QString("%1 %2").arg(tcpSocket->peerAddress().toString()).arg(tcpSocket->peerPort());
        strPeer.remove("::ffff:");
        addPeer(strPeer);
    }
}

void TcpServer::on_acceptError(QAbstractSocket::SocketError socketError)
{
    qWarning() << QString("TcpServer异常：%1").arg(socketError);
}

void TcpServer::on_disconnected()
{
    for(int i = 0; i < connects.count(); i++)
    {
        if(connects.at(i)->state() != QAbstractSocket::ConnectedState)       // 未连接
        {
            disconnect(connects.at(i), &QTcpSocket::disconnected, this, &TcpServer::on_disconnected);
            disconnect(connects.at(i), &QTcpSocket::readyRead, this, &TcpServer::on_readyRead);
            connects.takeAt(i)->deleteLater();       // 移除已经断开连接的Client（注意这里不能使用delete，否则在vs中会报错）
            QListWidgetItem * item = ui->listWidget->item(i);
            ui->listWidget->removeItemWidget(item);
            delete item;                    // 不加这一行 listwidget的count不会变化
            item = nullptr;
        }
    }
}

void TcpServer::on_readyRead()
{
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        if(connects.at(i)->bytesAvailable() <= 0) continue;       // 如果无可读数据则返回

        QByteArray arr = connects.at(i)->readAll();                // 读取数据
        QCheckBox* checkBox = (QCheckBox*)ui->listWidget->itemWidget(ui->listWidget->item(i));
        if(checkBox->isChecked())                                      // 勾选的已连接Client则显示接收的信息
        {
            if(arr.count() <= 0)
            {
                continue;
            }
            ui->spin_recv->setValue(ui->spin_recv->value() + arr.count());  // 统计接收的数据总大小
            QString strPeer = checkBox->text();
            if(ui->check_hexRecv->isChecked())
            {
                ui->text_recv->append(QString("[%1] ").arg(strPeer) + arr.toHex(' '));
            }
            else
            {
                ui->text_recv->append(QString("[%1] ").arg(strPeer) + arr);
            }
        }
    }
}

void TcpServer::on_btn_clearSend()
{
    ui->text_send->clear();
    ui->spin_send->setValue(0);
}

void TcpServer::on_btn_clearRev()
{
    ui->text_recv->clear();
    ui->spin_recv->setValue(0);
}

void TcpServer::on_check_hexRev(bool checked)
{
    QString value;
    if(checked)
    {
        value = ui->text_recv->toPlainText().toUtf8().toHex(' ');             // 01 02 03 1a 格式显示
    }
    else
    {
        value = QByteArray::fromHex(ui->text_recv->toPlainText().toUtf8());   // 123abc格式显示
    }
    ui->text_recv->setText(value);
}

void TcpServer::on_check_hexSend(bool checked)
{
    QString value;
    if(checked)
    {
        value = ui->text_send->toPlainText().toUtf8().toHex(' ');             // 01 02 03 1a 格式显示
    }
    else
    {
        value = QByteArray::fromHex(ui->text_send->toPlainText().toUtf8());   // 123abc格式显示
    }
    ui->text_send->setText(value);
}

void TcpServer::on_btn_send()
{
    QString str = ui->text_send->toPlainText();
#if 0
    QByteArray arr = str.toLocal8Bit();              // 根据编译器编码或者 QTextCodec::setCodecForLocale(codec);指定的编码方式将QString转换为QBytearray，一般为utf-8或者GBK，支持中文
#else
    QByteArray arr = str.toUtf8();                   // 指定以utf-8编码
#endif
    if(ui->check_hexSend->isChecked())               // 如果是16进制显示则转换
    {
        arr = QByteArray::fromHex(arr);
    }

    qint64 len = sendData(arr);
    if(len < 0)
    {
        qWarning() <<"发送失败！";
    }
    ui->spin_send->setValue(ui->spin_send->value() + len);
}

void TcpServer::on_btn_listen()
{
    if(!m_pTcpServer) return;

    if(!m_pTcpServer->isListening())          // 判断是否正在监听连接
    {
        // 告诉服务器侦听地址和端口上的传入连接。如果端口为0，则会自动选择一个端口。
        // 如果地址是QHostAddress:：Any，服务器将监听所有网络接口。
        bool ret = m_pTcpServer->listen(QHostAddress::Any, ui->spin_localPort->value());
        if(ret)
        {
            ui->but_connect->setText("停止");
        }
        else
        {
            qDebug() << QString("tcpServer绑定监听IP、端口失败：%1 %2").arg(m_pTcpServer->errorString()).arg(m_pTcpServer->serverError());
        }
    }
    else
    {
        m_pTcpServer->close();
        ui->but_connect->setText("开始监听");
        for(int i = connects.count() - 1; i >= 0 ; i--)          // 关闭所有连接的TCP Client
        {
            connects.at(i)->abort();
        }
    }
}
