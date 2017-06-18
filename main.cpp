#include "mainwindow.h"
#include <QApplication>
#include "ApiEx.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    int flg=a.exec();
    Cleanup();
    return flg;
}
