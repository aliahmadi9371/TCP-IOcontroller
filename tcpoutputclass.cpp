#include "tcpoutputclass.h"

TcpOutputClass::TcpOutputClass(QObject *parent) : QObject(parent)
{

}

void TcpOutputClass::func_InitVariables()
{
    port = 0;
    message = "";
    response = "";
    client = NULL;
    timeout = 0;
    number = -1;
    timer.setSingleShot(true);
}

void TcpOutputClass::func_GetSetting(int field_number)
{
    number = field_number;
    QSettings setting("IOController_config.ini",QSettings::IniFormat);
    QString key1 = "TCP_OUTPUT/port_output_";
    QString key2 = "TCP_OUTPUT/message_output_";
    QString key3 = "TCP_OUTPUT/response_ouput_";
    QString key4 = "TCP_OUTPUT/timer_output_";
    port = setting.value(key1 + QString::number(field_number),0).toInt();
    message = setting.value(key2 + QString::number(field_number),"").toString();
    response = setting.value(key3 + QString::number(field_number),"").toString();
    timeout = setting.value(key4 + QString::number(field_number),1000).toInt();

    qDebug()<< "TCPSERVER: [" << number << "] : port = " << port <<
               " , message = " <<  message <<
               " , response = " << response <<
               " , timeout = " << timeout;
}

void TcpOutputClass::func_ConfigClass()
{
    func_ListenOutPut();
}

void TcpOutputClass::func_ListenOutPut()
{
    if(server.listen(QHostAddress::Any,port)){
        QObject::connect(&server,SIGNAL(newConnection()),this, SLOT(slot_NewConnectSocketOutput()),Qt::QueuedConnection);
    }
    else{
        qDebug() << "TCPSERVER: [" << number << "]  error : " << server.errorString();
        exit(EXIT_FAILURE);
    }
}

void TcpOutputClass::slot_NewConnectSocketOutput()
{
    client = server.nextPendingConnection();
    qDebug() << "TCPSERVER: [" << number << "]  new connection pointer : " << client;
    QObject::connect(client, SIGNAL(readyRead()), this, SLOT(slot_ReadSocketOutput()), Qt::QueuedConnection);
}

void TcpOutputClass::slot_ReadSocketOutput()
{
    QString tmp = "";
    while(client->bytesAvailable())
        tmp.append(client->readAll());
    qDebug() << "TCPSERVER: [" << number << "]  receive socket pm : " << tmp;
    if(tmp == message){
        emit this->sig_GetValidCommand();
        qDebug() << "TCPSERVER: [" << number << "]  receive socket valid pm : " << tmp;
        if(response != ""){
            qDebug() << "TCPSERVER: [" << number << "]  send response : " << response;
            client->write(response.toLocal8Bit().data(),response.length());
        }
    }
    else{
        qDebug() << "TCPSERVER: [" << number << "]  receive socket invalid pm : " << tmp;
    }

}

