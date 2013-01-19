#ifndef TRACK_H
#define TRACK_H

#include <list>
#include <QDateTime>
#include <math.h>

#include "point.h"

namespace godwit
{

double haversine(double lon1, double lat1, double lon2, double lat2);

class Track
{
public:
    Track(std::list<Point>& points, std::string name, QDateTime timestamp);

    std::string getName() const{ return mName; }
    QDateTime getTimestamp() const{ return mTimestamp; }
    double getDistance() const{ return mDistance; }

private:
    std::list<Point> mPoints;
    std::string mName;
    QDateTime mTimestamp;
    double mDistance;
};

}

#endif // TRACK_H
