#ifndef TCPSERVER_H
#define TCPSERVER_H
#include "tcpclient.h"
#include <QWidget>
#include <QList>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class TcpServer;
}

class TcpServer : public QWidget
{
    Q_OBJECT

public:
    explicit TcpServer(QWidget *parent = nullptr);
    ~TcpServer();

private:
    void init();

    void connectSlots();

    void addPeer(const QString& peer);

    qint64 sendData(const QByteArray& data);
private slots:
    void on_newConnection();

    void on_acceptError(QAbstractSocket::SocketError socketError);

    void on_disconnected();

    void on_readyRead();

    void on_btn_clearSend();

    void on_btn_clearRev();

    void on_check_hexRev(bool checked);

    void on_check_hexSend(bool checked);

    void on_btn_send();

    void on_btn_listen();
private:
    Ui::TcpServer *ui;

    QTcpServer* m_pTcpServer = nullptr;
    QList<QTcpSocket *> connects;        //已连接的客户端
};

#endif // TCPSERVER_H
