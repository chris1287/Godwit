#include "GeoUtils.h"

namespace godwit
{

double decimal2radians(double x)
{
    return x * pi() / 180;
}

double haversine(double lat1, double lon1, double lat2, double lon2)
{
    using namespace std;
    double dx, dy, dz;

    lat1 -= lat2;
    lat1 = decimal2radians(lat1); lon1 = decimal2radians(lon1);
    lat2 = decimal2radians(lat2); lon2 = decimal2radians(lon2);

    dz = sin(lon1) - sin(lon2);
    dx = cos(lat1) * cos(lon1) - cos(lon2);
    dy = sin(lat1) * cos(lon1);
    double res = asin(sqrt(dx * dx + dy * dy + dz * dz) / 2) * 2 * earth_radius();

    return res;
}

}
