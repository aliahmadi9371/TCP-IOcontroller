#include "tcpinputclass.h"

TcpInputClass::TcpInputClass(QObject *parent) : QObject(parent)
{

}

void TcpInputClass::func_InitVariables()
{
    ip = "";
    port = -1;
    message = "";
    connect = false;
    number = -1;
    timer.setSingleShot(false);
}

void TcpInputClass::func_GetSetting(int field_number)
{
    number = field_number;
    QSettings setting("IOController_config.ini",QSettings::IniFormat);
    QString key1 = "TCP_INPUT/ip_input_";
    QString key2 = "TCP_INPUT/port_input_";
    QString key3 = "TCP_INPUT/message_input_";
    ip = setting.value(key1 + QString::number(number),"").toString();
    port = setting.value(key2 + QString::number(number),0).toInt();
    message = setting.value(key3 + QString::number(number),"").toString();

    qDebug()<< "TCPCLIENT: [" << number << "] : ip = " << ip <<
               " , port = " <<  port <<
               " , message = " <<  message;
}

void TcpInputClass::func_ConfigClass()
{
    QObject::connect(&timer,SIGNAL(timeout()),this, SLOT(slot_CheckSocket()),Qt::QueuedConnection);
    qRegisterMetaType<QAbstractSocket::SocketState>();
    QObject::connect(&socket,SIGNAL(stateChanged(QAbstractSocket::SocketState)),this, SLOT(slot_ChangedState(QAbstractSocket::SocketState)),Qt::QueuedConnection);
    socket.connectToHost(QHostAddress(ip),port);
    timer.start(500);
}

void TcpInputClass::slot_CheckSocket()
{
   if(connect == false && !(socket.state() == QAbstractSocket::HostLookupState || socket.state() == QAbstractSocket::ConnectingState)){        socket.close();
       qDebug() << "TCPCLIENT: [" << number << "] connection try to" << ip << ":" << port;
       socket.connectToHost(QHostAddress(ip),port);
   }
}

void TcpInputClass::func_SendMessage()
{
    qDebug() << "TCPCLIENT: [" << number << "] send message : " << message;
    if(socket.state() == QAbstractSocket::ConnectedState){
        qDebug() << "TCPCLIENT: [" << number << "] socket open";
        socket.write(message.toLocal8Bit().data(),message.length());
        qDebug() << "TCPCLIENT: [" << number << "] send message to " << ip << ":" << port;
    }
    else if(socket.state() == QAbstractSocket::UnconnectedState){
        qDebug() << "TCPCLIENT: [" << number << "] socket in not connected";
        socket.connectToHost(QHostAddress(ip),port);
        qDebug() << "TCPCLIENT: [" << number << "] socket open";
        socket.write(message.toLocal8Bit().data(),message.length());
        qDebug() << "TCPCLIENT: [" << number << "] send message to " << ip << ":" << port;
    }
}

void TcpInputClass::slot_ChangedState(QAbstractSocket::SocketState socketState)
{
    switch (socketState) {
    case 0:
        qDebug() << "TCPCLIENT: [" << number << "] socket state from host : "
                 << ip << ":" << port << " is " << socketState;
        connect = false;
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        qDebug() << "TCPCLIENT: [" << number << "] socket state from host : "
                 << ip << ":" << port << " is " << socketState;
        connect = true;
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        break;
    default:
        break;
    }
}



