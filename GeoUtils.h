#ifndef GEOUTILS_H
#define GEOUTILS_H

#include <math.h>

namespace godwit
{

constexpr double pi() { return atan(1.0) * 4; }
constexpr double earth_radius() { return 6371; }

double decimal2radians(double x);

double haversine(double lat1, double lon1, double lat2, double lon2);

}

#endif // GEOUTILS_H
