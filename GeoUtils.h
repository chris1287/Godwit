#ifndef GEOUTILS_H
#define GEOUTILS_H

#include <math.h>

namespace godwit
{

constexpr double pi() { return atan(1.0) * 4; }
constexpr double earth_radius() { return 6367; }

double decimal2radians(double x);

double haversine(double lat1, double lon1, double lat2, double lon2);

int long2tilex(double lon, int zoom);

int lat2tiley(double lat, int zoom);

double tilex2long(int x, int zoom);

double tiley2lat(int y, int zoom);

}

#endif // GEOUTILS_H
