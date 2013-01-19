#include <QDebug>

#include "track.h"

namespace godwit
{

Track::Track(std::list<Point>& points, std::string name = "", QDateTime timestamp = QDateTime::currentDateTime())
{
    mPoints = points;
    mName = name;
    mTimestamp = timestamp;

    auto delta = [](Point a, Point b)
    {
        return haversine(a.getLongitude(), a.getLatitude(), b.getLongitude(), b.getLatitude()) ;
    };

    mDistance = 0.0;

    if(points.size() >= 2)
    {
        auto i = points.begin();
        auto j = points.begin();
        while(++j != points.end())
        {
            mDistance += delta(*i, *j);
            i = j;
        }
    }
}

constexpr double pi() { return std::atan(1.0) * 4; }
constexpr double earth_radius() { return 6371; }

double decimal2radians(double x)
{
    return x * pi() / 180;
}

double haversine(double lon1, double lat1, double lon2, double lat2)
{
    using namespace std;
    double dx, dy, dz;

//    qDebug() << "haversine( " << lon1 << "," << lat1 << "; " << lon2 << "," << lat2 << ")" << "\n";

    lat1 -= lat2;
    lat1 = decimal2radians(lat1); lon1 = decimal2radians(lon1);
    lat2 = decimal2radians(lat2); lon2 = decimal2radians(lon2);

    dz = sin(lon1) - sin(lon2);
    dx = cos(lat1) * cos(lon1) - cos(lon2);
    dy = sin(lat1) * cos(lon1);
    return asin(sqrt(dx * dx + dy * dy + dz * dz) / 2) * 2 * earth_radius();
}

}
