#ifndef MESSAGE_H
#define MESSAGE_H
#include <QThread>
#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<string.h>
#include "ApiEx.h"
#include "userdata.h"
#include <QThread>
#include <QDebug>
#define MAXSIZE 10
#define LENGTH 10


class MESSAGE : public QThread
{
    Q_OBJECT
public:
    MESSAGE();
    void run();
    void receiveByte();
    void sendByte(char toSend);
    void Init8251();
private:
    const int PORT8251DATA = 0x2b8; //8251数据口
    const int PORT8251INST = 0x2b9; //8251命令&状态口
signals:
    void getdata(char);

};

#endif // MESSAGE_H
