#include <QApplication>
#include <iostream>
#include <list>
#include <QDateTime>

// #include "marble/MarbleWidget.h"

#include "mainwindow.h"
#include "point.h"
#include "track.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
