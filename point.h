#ifndef POINT_H
#define POINT_H

#include <QDateTime>

namespace godwit
{

class Point_creation_exception : public std::exception
{
    virtual const char* what() const throw()
    {
        return "Failed to create a point";
    }
};

typedef std::pair<double, double> latlon;

class Point
{
public:
    Point(double longitude, double latitude, double altitude, int heartRate, QDateTime timestamp);

    bool equals(const Point& that) const;
    bool operator == (const Point& that) const;
    bool operator != (const Point& that) const;

    double getLatitude() const{ return mLatitude; }
    double getLongitude() const{ return mLongitude; }
    double getAltitude() const{ return mAltitude; }
    int getHeartRate() const{ return mHeartRate; }
    QDateTime getTimestamp() const{ return mTimestamp; }
    latlon getLatLon() const{ return latlon(mLatitude, mLongitude); }

private:
    double mLatitude;
    double mLongitude;
    double mAltitude;
    int mHeartRate;
    QDateTime mTimestamp;
};

}

#endif // POINT_H
