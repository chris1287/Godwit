#include <QApplication>
#include <iostream>
#include <list>
#include <QDateTime>

#include "mainwindow.h"
#include "point.h"
#include "track.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    std::cout << godwit::haversine(44.404293, 7.792286, 44.383502, 8.023427) << std::endl;
    std::cout << godwit::haversine(44.404293, 7.792286, 44.382651, 7.773984) << std::endl;

    std::list<godwit::Point> l
    {
        godwit::Point(44.404293, 7.792286, 0, 0, QDateTime::currentDateTime()),
        godwit::Point(44.383502, 8.023427, 0, 0, QDateTime::currentDateTime()),
    };

    godwit::Track t(l, "", QDateTime::currentDateTime());

    std::cout << t.getDistance() << std::endl;

    return a.exec();
}
