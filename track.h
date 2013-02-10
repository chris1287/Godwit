#ifndef TRACK_H
#define TRACK_H

#include <list>
#include <QDateTime>
#include <QDomElement>

#include "point.h"

namespace godwit
{

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
    Track();
    Track(std::list<Point>& points, std::string name, QDateTime timestamp);
    Track(const QString &fileName);

public:
    std::string getName() const{ return mName; }
    QDateTime getTimestamp() const{ return mTimestamp; }
    double getDistance() const{ return mDistance; }
    Point getStart() const{ return mPoints.front(); }
    Point getEnd() const{ return mPoints.back(); }
    std::list<Point> getPoints() const{ return mPoints; }

private:
    void init(std::list<Point>& points, std::string name, QDateTime timestamp);

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
