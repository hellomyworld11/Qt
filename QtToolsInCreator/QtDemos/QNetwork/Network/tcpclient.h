#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QWidget>
#include <QTcpSocket>



namespace Ui {
class TcpClient;
}

class TcpClient : public QWidget
{
    Q_OBJECT

public:
    explicit TcpClient(QWidget *parent = nullptr);
    ~TcpClient();

private:
    void init();

    void connectSlots();

private slots:
    void on_connected();

    void on_disconnected();

    void on_stateChanged(QAbstractSocket::SocketState state);

    void on_errorOccurred(QAbstractSocket::SocketError error);

    void on_readyRead();

    void on_but_connect_clicked();

    void on_but_send_clicked();

    void on_but_clearSend_clicked();

    void on_check_hexSend_clicked(bool checked);

    void on_check_hexRecv_clicked(bool checked);

    void on_but_clearRecv_clicked();

private:
    Ui::TcpClient *ui;

    QTcpSocket* m_pTcpClient = nullptr;
};

#endif // TCPCLIENT_H
