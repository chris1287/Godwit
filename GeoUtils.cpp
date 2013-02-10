#include "GeoUtils.h"

namespace godwit
{

double decimal2radians(double x)
{
    return x * pi() / 180;
}

double haversine(double lat1, double lon1, double lat2, double lon2)
{
	double dlon = 0.0;
	double dlat = 0.0;
	double a = 0.0;
	double c = 0.0;
	double res = 0.0;

    lat1 = decimal2radians(lat1); lon1 = decimal2radians(lon1);
    lat2 = decimal2radians(lat2); lon2 = decimal2radians(lon2);

	dlon = lon2 - lon1;
	dlat = lat2 - lat1;

	a = pow(sin(dlat/2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlon/2), 2);
	c = 2 * asin(sqrt(a));

	res = earth_radius() * c;

    return res;
}

int long2tilex(double lon, int zoom)
{
    return (int)(floor((lon + 180.0) / 360.0 * pow(2.0, zoom)));
}

int lat2tiley(double lat, int zoom)
{
    return (int)(floor((1.0 - log( tan(lat * pi()/180.0) + 1.0 / cos(lat * pi()/180.0)) / pi()) / 2.0 * pow(2.0, zoom)));
}

double tilex2long(int x, int zoom)
{
    return x / pow(2.0, zoom) * 360.0 - 180;
}

double tiley2lat(int y, int zoom)
{
    double n = pi() - 2.0 * pi() * y / pow(2.0, zoom);
    return 180.0 / pi() * atan(0.5 * (exp(n) - exp(-n)));
}

}
