#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "userdata.h"
#include "message.h"
#include "QDebug"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void MachineLeft();
    void MachineRight();
    ~MainWindow();

private slots:
    void handerdate(char ch);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    const int PORT8255INST = 0x28b; //8255命令&状态口
    const int PORT8255A= 0x288;
    const int PORT8255B= 0x289;
    const int PORT8255C= 0x28a;
    Ui::MainWindow *ui;
    MESSAGE message;
    UserData userData;
    int Data;
    int User;
    int State = 0;
    User1 user1;
    User2 user2;
    int balance1;
    int balance2;
};

#endif // MAINWINDOW_H
