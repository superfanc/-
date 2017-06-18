#ifndef MASSAGE_H
#define MASSAGE_H


#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<string.h>
#include "ApiEx.h"
#include "userdata.h"
#include <QThread>
#define MAXSIZE 10
#define LENGTH 10

#define data51 0x308    //8251A数据口
#define ctrl51 0x309	   //8251A命令/状态口
#define ctrl55 0x303    //8255命令口
#define timer2 0x306    //8253的2号计数器端口
#define timctl 0x307    //8253命令口


class massage: public QThread
{
    Q_OBJECT
private:
    const int PORT8251DATA = 0x308; //8251数据口
    const int PORT8251INST = 0x309; //8251命令&状态口
public:
    massage();
    void run();
    char receiveByte();             //接收1位有效数据
    void sendByte(char toSend);     //发送1位数据

};

#endif // MASSAGE_H
