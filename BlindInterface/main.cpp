#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.init("test","127.0.0.1","player1");
    w.show();

    return a.exec();
}
