#ifndef TRACK_H
#define TRACK_H

#include <list>
#include <QDateTime>
#include <QDomElement>

#include "point.h"

namespace godwit
{

double haversine(double lon1, double lat1, double lon2, double lat2);

class Track_creation_exception : public std::exception
{
    virtual const char* what() const throw()
    {
        return "Failed to create a track";
    }
};

class Track
{
public:
    Track(std::list<Point>& points, std::string name, QDateTime timestamp);
    static Track createTrackFromGPX(const QString& fileName);
    std::string getName() const{ return mName; }
    QDateTime getTimestamp() const{ return mTimestamp; }
    double getDistance() const{ return mDistance; }

private:
    static double retrieveDoubleAttribute(const QDomElement& e, const QString& attr);
    static double retrieveDoubleSingleChild(const QDomElement& e, const QString& tag);
    static QDateTime retrieveQDateTimeSingleChild(const QDomElement& e, const QString& tag);
    static QString getDateTimeFormat() { return mDateTimeFormat; }
    static void setDateTimeFormat(const QString& dateTimeFormat) { mDateTimeFormat = dateTimeFormat; }

private:
    std::list<Point> mPoints;
    std::string mName;
    QDateTime mTimestamp;
    double mDistance;
    static QString mDateTimeFormat;
};

}

#endif // TRACK_H
