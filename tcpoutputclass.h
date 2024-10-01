#ifndef TCPOUTPUTCLASS_H
#define TCPOUTPUTCLASS_H

#include <QObject>
#include <QDebug>
#include <QSettings>
#include <QAbstractSocket>
#include <QTcpSocket>
#include <QTcpServer>
#include <QTimer>

class TcpOutputClass : public QObject
{
    Q_OBJECT
public:
    explicit TcpOutputClass(QObject *parent = 0);
    void func_InitVariables();
    void func_ConfigClass();
    void func_GetSetting(int field_number);
    void func_ListenOutPut();


    int port;
    QString message;
    QString response;
    QTcpServer server;
    QTcpSocket *client;
    int timeout;
    QTimer timer;
    int number;

signals:
    void sig_GetValidCommand();
public slots:
    void slot_NewConnectSocketOutput();
    void slot_ReadSocketOutput();
};

#endif // TCPOUTPUTCLASS_H
