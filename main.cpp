#include <QApplication>
#include <iostream>
#include <list>
#include <QDateTime>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
