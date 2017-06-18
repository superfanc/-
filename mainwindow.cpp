#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Startup();
    ui->setupUi(this);
    message.Init8251();
    connect(&message,SIGNAL(getdata(char)),this,SLOT(handerdate(char)));
    message.start();

}

void MainWindow::MachineLeft()  //退卡，电动机逆时针
{
    int i;
    int p = 0;
    unsigned char PSTA[8] = {0x05,0x15,0x14,0x54,0x50,0x51,0x41,0x45};
    qDebug()<<"write 1"<<PortWriteByte(PORT8255INST, 0x81);
    PortWriteByte(PORT8255INST,0x0E);
    while(1){
        for(i=7;i>=0;i--){
           p++;
           //qDebug()<<i;
           PortWriteByte(PORT8255A, PSTA[i]);
           Sleep(0.5);
           PortReadByte(PORT8255C, (BYTE *)&Data);
           //qDebug()<<i;
           if(Data&0x02 == 0){
              PortWriteByte(PORT8255INST, 0x09);
              return;
           }
        }
        if(i==-1) i=7;
        if(p>1800) {PortWriteByte(PORT8255INST,0x0F);return;}
    }
}

void MainWindow::MachineRight()
{
    int i;
    int p = 0;
    unsigned char PSTA[8] = {0x05,0x15,0x14,0x54,0x50,0x51,0x41,0x45};
    qDebug()<<"write 1"<<PortWriteByte(PORT8255INST, 0x81);
    PortWriteByte(PORT8255INST,0x0E);
    while(1){
        for(i=0;i<=7;i++){
           p++;
           PortWriteByte(PORT8255A, PSTA[i]);
           Sleep(0.5);
           PortReadByte(PORT8255C, (BYTE *)&Data);
           if(Data&0x02 == 0){
              PortWriteByte(PORT8255INST, 0x09);
              return;
           }
        }
        if(i==8) i=0;
        if(p>1800) {PortWriteByte(PORT8255INST,0x0F);return;}
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::handerdate(char ch)
{
    if(State ==0){
    if(ch == 1){
        User = 1;
        ui->label_2->setText("1");
        message.sendByte(1);
        State = 1;

    }
    else if(ch ==7){    //进卡，不需要返回
        MainWindow::MachineRight();
    }
    else if(ch == 2){
        User = 2;
        ui->label_2->setText("2");
        message.sendByte(1);
        State = 1;
    }
    else{
        message.sendByte(0);
        return;
    }
    }
    else if(State ==1){
        if(User == 1){
            if(ch == 123){
                message.sendByte(1);
                ui->label_4->setText("123");
                State = 3;
            }
            else {
                message.sendByte(0);
                ui->label_4->setText("密码错误");
                State = 0;
            }
        }
        else{
            if(ch == 10){
                message.sendByte(1);
                ui->label_4->setText("10");
                State = 3;
            }
            else {
                message.sendByte(0);
                ui->label_4->setText("密码错误");
                State = 0;
            }
        }
    }
    else if(State == 3){
        if(ch == 3){    //当接收到3的时候发送余额
            if(User == 1){
                qDebug("balance1:%d",user1.Balance);
                message.sendByte(user1.Balance);
            }
            else{
                qDebug("balance2:%d",user2.Balance);
                message.sendByte(user2.Balance);
            }
        }
        else if(ch == 4){  //取钱，返回1，状态变为4
            message.sendByte(1);
            State = 4;
        }
        else if(ch == 5){  //存钱，返回1，状态变为5
            message.sendByte(1);
            State = 5;
        }
        else if(ch == 6){  //退卡，返回1,状态变为0
            message.sendByte(1);
            MainWindow::MachineLeft();
            State = 0;
            User = 0;
        }
        else{
            qDebug()<<"exit 3";
        }
    }
    else if(State ==4){
        if(User == 1){
            user1.Balance = user1.Balance - ch;
            if(user1.Balance < 0){
                message.sendByte(0);
                user1.Balance = user1.Balance + ch;
                State = 3;
            }
            else{
                State = 3;
                message.sendByte(1);
            }
        }
        else{
            user2.Balance = user2.Balance - ch;
            if(user2.Balance < 0){
                message.sendByte(0);
                user2.Balance = user2.Balance + ch;
                State = 3;
            }
            else{
                State = 3;
                message.sendByte(1);
            }
        }
    }
    else if(State == 5){
        if(User == 1){
            user1.Balance = user1.Balance + ch;
            State = 3;
        }
        else{
            user2.Balance = user2.Balance + ch;
            State = 3;
        }
    }
    else{
        qDebug()<<"exit 4";
    }
}

void MainWindow::on_pushButton_clicked()
{
    MainWindow::MachineLeft();
    qDebug()<<"left";
}

void MainWindow::on_pushButton_2_clicked()
{

    MainWindow::MachineRight();
    qDebug()<<"right";
}
