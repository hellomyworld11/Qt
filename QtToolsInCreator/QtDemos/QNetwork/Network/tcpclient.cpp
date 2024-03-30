#include "tcpclient.h"
#include "ui_tcpclient.h"

TcpClient::TcpClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TcpClient)
{
    ui->setupUi(this);

    setWindowTitle("tcp客户端");

    init();

    connectSlots();
}

TcpClient::~TcpClient()
{
    delete ui;
}

void TcpClient::init()
{
    m_pTcpClient = new QTcpSocket(this);
    ui->line_localAddress->setText("127.0.0.1");
}

void TcpClient::connectSlots()
{
    connect(m_pTcpClient, &QTcpSocket::connected, this, &TcpClient::on_connected);
    connect(m_pTcpClient, &QTcpSocket::disconnected, this, &TcpClient::on_disconnected);
    connect(m_pTcpClient, &QTcpSocket::stateChanged, this, &TcpClient::on_stateChanged);
    connect(m_pTcpClient, &QTcpSocket::readyRead, this, &TcpClient::on_readyRead);

    connect(ui->but_connect, &QPushButton::clicked, this, &TcpClient::on_but_connect_clicked);
    connect(ui->but_send, &QPushButton::clicked, this, &TcpClient::on_but_send_clicked);
    connect(ui->but_clearRecv, &QPushButton::clicked, this, &TcpClient::on_but_clearRecv_clicked);
    connect(ui->but_clearSend, &QPushButton::clicked, this, &TcpClient::on_but_clearSend_clicked);
    connect(ui->check_hexRecv, &QCheckBox::clicked, this, &TcpClient::on_check_hexRecv_clicked);
    connect(ui->check_hexSend, &QCheckBox::clicked, this, &TcpClient::on_check_hexSend_clicked);


#if (QT_VERSION <= QT_VERSION_CHECK(5,15,0))        // qt5.15 后error已经弃用，这里改用errorOccurred
    connect(m_pTcpClient, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
            this, &TcpClient::on_errorOccurred);    // 由于QAbstractSocket中有两个error()，所以不能直接使用Qt5的信号槽绑定方式
#else
    connect(m_tcpClient, &QTcpSocket::errorOccurred, this, &TCPClient::on_errorOccurred);
#endif
}

void TcpClient::on_connected()
{
    ui->but_connect->setText("断开连接");
    ui->spin_localPort->setValue(m_pTcpClient->localPort());
    qInfo() << QString("成功连接：%1 %2").arg(m_pTcpClient->peerName()).arg(m_pTcpClient->peerPort());
}

void TcpClient::on_disconnected()
{
    ui->but_connect->setText("连接");
    qInfo() <<QString("断开连接：%1 %2").arg(m_pTcpClient->peerName()).arg(m_pTcpClient->peerPort());
}

void TcpClient::on_stateChanged(QAbstractSocket::SocketState state)
{
    qInfo() << "状态改变："<< state;
}

void TcpClient::on_errorOccurred(QAbstractSocket::SocketError error)
{
    qWarning() << "出现异常：" <<error;
}

void TcpClient::on_readyRead()
{
    QByteArray arr = m_pTcpClient->readAll();

    if(arr.count() <= 0)
    {
        return;
    }
    ui->spin_recv->setValue(ui->spin_recv->value() + arr.count());
    if(ui->check_hexRecv->isChecked())
    {
        ui->text_recv->append(arr.toHex(' '));
    }
    else
    {
        ui->text_recv->append(arr);
    }
}

void TcpClient::on_but_connect_clicked()
{
    if(!m_pTcpClient) return;

    if(m_pTcpClient->state() == QAbstractSocket::UnconnectedState)         // 判断连接状态
    {
        m_pTcpClient->connectToHost(ui->line_peerAddress->text(), ui->spin_peerPort->value());
    }
    else
    {
#if 1   // 使用abort函数立即关闭套接字，丢弃写入缓冲区中的任何未决数据。
        m_pTcpClient->abort();

#else   // 等待数据发送完成再关闭

#if 0
        m_tcpClient->disconnectFromHost();  // 不一定立即关闭，如果有待写入的数据等待写入，将进入 ClosingState状态 并等待所有数据写入完毕
#else
        m_tcpClient->close();               // 关闭 QIODevice并调用disconnectFromHost
#endif
        qDebug() <<"IO状态：" << m_tcpClient->isOpen();                 // 可通过这一行代码测试Close和disconnectFromHost的区别
        if (m_tcpClient->state() == QAbstractSocket::UnconnectedState) // 如果调用close后没有立即关闭则等待 1秒中
        {
            if(m_tcpClient->waitForDisconnected(1000))
            {
                qInfo() <<"关闭成功!";
            }
            else
            {
                qWarning() << "关闭失败："<<m_tcpClient->error();
            }
        }
#endif
    }
}

void TcpClient::on_but_send_clicked()
{
    if(!m_pTcpClient) return;
    if(m_pTcpClient->state() != QAbstractSocket::ConnectedState) return;  // 判断是否已连接

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

    qint64 len = m_pTcpClient->write(arr);
    if(len < 0)
    {
        qWarning() <<"发送失败！";
    }
    ui->spin_send->setValue(ui->spin_send->value() + len);
}

/**
 * @brief 清空接收区
 */
void TcpClient::on_but_clearRecv_clicked()
{
    ui->text_recv->clear();
    ui->spin_recv->setValue(0);
}

/**
 * @brief 清空发送区
 */
void TcpClient::on_but_clearSend_clicked()
{
    ui->text_send->clear();
    ui->spin_send->setValue(0);
}

/**
 * @brief           将发送区内容转换为十六进制显示
 * @param checked
 */
void TcpClient::on_check_hexSend_clicked(bool checked)
{
    QString value;
    if(checked)
    {
        value = ui->text_send->toPlainText().toUtf8().toHex(' ');
    }
    else
    {
        value = QByteArray::fromHex(ui->text_send->toPlainText().toUtf8());
    }
    ui->text_send->setText(value);
}

/**
 * @brief          将接收区内容转换为十六进制显示
 * @param checked
 */
void TcpClient::on_check_hexRecv_clicked(bool checked)
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
