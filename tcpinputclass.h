#ifndef TCPINPUTCLASS_H
#define TCPINPUTCLASS_H

#include <QObject>
#include <QDebug>
#include <QSettings>
#include <QAbstractSocket>
#include <QTcpSocket>
#include <QTimer>
#include <QHostAddress>

class TcpInputClass : public QObject
{
    Q_OBJECT
public:
    explicit TcpInputClass(QObject *parent = 0);
    void func_InitVariables();
    void func_GetSetting(int field_number);
    void func_ConfigClass();
    void func_SendMessage();

    int port;
    QString ip;
    QString message;
    QTcpSocket socket;
    bool connect;
    int number;
    QTimer timer;
signals:

public slots:
    void slot_CheckSocket();
    void slot_ChangedState(QAbstractSocket::SocketState socketState);
};

#endif // TCPINPUTCLASS_H
