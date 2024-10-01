#ifndef MAINCLASS_H
#define MAINCLASS_H

#include <QObject>
#include <QDebug>
#include <QSettings>
#include <wiringPi.h>
#include <QTimer>

#include "tcpoutputclass.h"
#include "tcpinputclass.h"

#define OOUT1 12    //GPIO.1    OUT1
#define OOUT2 16    //GPIO.4    OUT2
#define OOUT3 18    //GPIO.5    OUT3
#define OOUT4 26    //GPIO.11   OUT4

#define IINP1 7     //GPIO.7    IN1
#define IINP2 29    //GPIO.21   IN2
#define IINP4 31    //GPIO.22   IN4
#define IINP3 33    //GPIO.23   IN3
#define IINP5 35    //GPIO.24   IN5
#define IINP6 37    //GPIO.25   IN6


class MainClass : public QObject
{
    Q_OBJECT
public:
    explicit MainClass(QObject *parent = 0);
    ~MainClass();

    void func_StartClass();
private:
    void func_InitVariables();
    void func_GetSetting();
    void func_SetWiringOPI();  

    TcpInputClass myTcpInput[6];
    TcpOutputClass myTcpOutput[4];
signals:
    void sing_InputDetect(int input_number);

public slots:
private slots:
    void slot_ReceiveInputSignal(int input_number);

    void slot_Output1();
    void slot_timeout1();
    void slot_Output2();
    void slot_timeout2();
    void slot_Output3();
    void slot_timeout3();
    void slot_Output4();
    void slot_timeout4();

};

#endif // MAINCLASS_H
