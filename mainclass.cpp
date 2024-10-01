#include "mainclass.h"

static MainClass* main_ptr = NULL;
static bool bool_input1 = false;
static bool bool_input2 = false;
static bool bool_input3 = false;
static bool bool_input4 = false;
static bool bool_input5 = false;
static bool bool_input6 = false;

void readiput1()
{
    if(main_ptr && !bool_input1){
        bool_input1 = true;
        emit main_ptr->sing_InputDetect(1);
    }
}

void readiput2()
{
    if(main_ptr && !bool_input2){
        bool_input2 = true;
        emit main_ptr->sing_InputDetect(2);
    }
}

void readiput3()
{
    if(main_ptr && !bool_input3){
        bool_input3 = true;
        emit main_ptr->sing_InputDetect(3);
    }
}

void readiput4(){
    if(main_ptr && !bool_input4){
        bool_input4 = true;
        emit main_ptr->sing_InputDetect(4);
    }
}

void readiput5()
{
    if(main_ptr && !bool_input5){
        bool_input5 = true;
        emit main_ptr->sing_InputDetect(5);
    }
}

void readiput6()
{
    if(main_ptr && !bool_input6){
        bool_input6 = true;
        emit main_ptr->sing_InputDetect(6);
    }
}

MainClass::MainClass(QObject *parent) : QObject(parent)
{

}

MainClass::~MainClass()
{
    delete this;
}

void MainClass::func_StartClass()
{
    qDebug() << "MAINCLASS:  START MAIN CLASS";
    main_ptr = this;
    func_InitVariables();
    func_GetSetting();
    func_SetWiringOPI();
}

void MainClass::func_InitVariables()
{

    for(int i=0; i<6; i++){
        myTcpInput[i].func_InitVariables();
        myTcpInput[i].func_GetSetting(i+1);
        myTcpInput[i].func_ConfigClass();
    }

    for(int i=0; i<4; i++){
        myTcpOutput[i].func_InitVariables();
        myTcpOutput[i].func_GetSetting(i+1);
        myTcpOutput[i].func_ConfigClass();
    }
    connect(&(myTcpOutput[0].timer),SIGNAL(timeout()), this,SLOT(slot_timeout1()),Qt::QueuedConnection);
    connect(&(myTcpOutput[1].timer),SIGNAL(timeout()), this,SLOT(slot_timeout2()),Qt::QueuedConnection);
    connect(&(myTcpOutput[2].timer),SIGNAL(timeout()), this,SLOT(slot_timeout3()),Qt::QueuedConnection);
    connect(&(myTcpOutput[3].timer),SIGNAL(timeout()), this,SLOT(slot_timeout4()),Qt::QueuedConnection);

    connect(&(myTcpOutput[0]),SIGNAL(sig_GetValidCommand()), this,SLOT(slot_Output1()),Qt::QueuedConnection);
    connect(&(myTcpOutput[1]),SIGNAL(sig_GetValidCommand()), this,SLOT(slot_Output2()),Qt::QueuedConnection);
    connect(&(myTcpOutput[2]),SIGNAL(sig_GetValidCommand()), this,SLOT(slot_Output3()),Qt::QueuedConnection);
    connect(&(myTcpOutput[3]),SIGNAL(sig_GetValidCommand()), this,SLOT(slot_Output4()),Qt::QueuedConnection);
}

void MainClass::func_GetSetting()
{
    QSettings setting("IOController.ini",QSettings::IniFormat);
}

void MainClass::func_SetWiringOPI()
{
    wiringPiSetupPhys();


    pinMode(OOUT1,OUTPUT);
    pinMode(OOUT2,OUTPUT);
    pinMode(OOUT3,OUTPUT);
    pinMode(OOUT4,OUTPUT);

    pinMode(IINP1,INPUT);
    pinMode(IINP2,INPUT);
    pinMode(IINP3,INPUT);
    pinMode(IINP4,INPUT);
    pinMode(IINP5,INPUT);
    pinMode(IINP6,INPUT);

    pullUpDnControl(OOUT1, PUD_DOWN);
    pullUpDnControl(OOUT2, PUD_DOWN);
    pullUpDnControl(OOUT3, PUD_DOWN);
    pullUpDnControl(OOUT4, PUD_DOWN);

    pullUpDnControl(IINP1, PUD_UP);
    pullUpDnControl(IINP2, PUD_UP);
    pullUpDnControl(IINP3, PUD_UP);
    pullUpDnControl(IINP4, PUD_UP);
    pullUpDnControl(IINP5, PUD_UP);
    pullUpDnControl(IINP6, PUD_UP);

    wiringPiISR(IINP1, INT_EDGE_FALLING, &readiput1);
    wiringPiISR(IINP2, INT_EDGE_FALLING, &readiput2);
    wiringPiISR(IINP3, INT_EDGE_FALLING, &readiput3);
    wiringPiISR(IINP4, INT_EDGE_FALLING, &readiput4);
    wiringPiISR(IINP5, INT_EDGE_FALLING, &readiput5);
    wiringPiISR(IINP6, INT_EDGE_FALLING, &readiput6);

    connect(this,SIGNAL(sing_InputDetect(int)),
            this,SLOT(slot_ReceiveInputSignal(int)),
            Qt::QueuedConnection);
}

void MainClass::slot_ReceiveInputSignal(int input_number)
{

    switch (input_number) {
    case 1:
        qDebug() << "MAINCLASS: receive input : " << 1;
        myTcpInput[input_number-1].func_SendMessage();
        bool_input1 = false;
        break;
    case 2:
        qDebug() << "MAINCLASS: receive input : " << 2;
        myTcpInput[input_number-1].func_SendMessage();
        bool_input2 = false;
        break;
    case 3:
        qDebug() << "MAINCLASS: receive input : " << 3;
        myTcpInput[input_number-1].func_SendMessage();
        bool_input3 = false;
        break;
    case 4:
        qDebug() << "MAINCLASS: receive input : " << 4;
        bool_input4 = false;
        myTcpInput[input_number-1].func_SendMessage();
        break;
    case 5:
        qDebug() << "MAINCLASS: receive input : " << 5;
        myTcpInput[input_number-1].func_SendMessage();
        bool_input5 = false;
        break;
    case 6:
        qDebug() << "MAINCLASS: receive input : " << 6;
        bool_input6 = false;
        myTcpInput[input_number-1].func_SendMessage();
        break;
    default:
        break;
    }
}

void MainClass::slot_Output1()
{
    digitalWrite(OOUT1,1);
    myTcpOutput[0].timer.start(myTcpOutput[0].timeout);
}

void MainClass::slot_timeout1()
{
    digitalWrite(OOUT1,0);
}

void MainClass::slot_Output2()
{
    digitalWrite(OOUT2,1);
    myTcpOutput[1].timer.start(myTcpOutput[1].timeout);
}

void MainClass::slot_timeout2()
{
    digitalWrite(OOUT2,0);
}

void MainClass::slot_Output3()
{
    digitalWrite(OOUT3,1);
    myTcpOutput[2].timer.start(myTcpOutput[2].timeout);
}

void MainClass::slot_timeout3()
{
    digitalWrite(OOUT3,0);
}

void MainClass::slot_Output4()
{
    digitalWrite(OOUT4,1);
    myTcpOutput[3].timer.start(myTcpOutput[3].timeout);
}

void MainClass::slot_timeout4()
{
    digitalWrite(OOUT4,0);
}
