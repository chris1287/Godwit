#ifndef COLORFACTORY_H
#define COLORFACTORY_H

#include <QColor>
#include <vector>

using namespace std;

static const vector<QColor> availableColors =
{
    Qt::green,
    Qt::black,
    Qt::red,
    Qt::blue,
    Qt::cyan,
    Qt::magenta,
    Qt::yellow,
    Qt::gray,
    Qt::darkGreen,
    Qt::darkRed,
    Qt::darkBlue,
    Qt::darkCyan,
    Qt::darkMagenta,
    Qt::darkYellow,
    Qt::darkGray,
    Qt::lightGray
};

QColor getNextColor()
{
    static int currentColor = -1;

    currentColor = (currentColor + 1) % availableColors.size();

    return availableColors.at(currentColor);
}

#endif // COLORFACTORY_H
