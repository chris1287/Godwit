#include <QDebug>
#include <QFile>
#include <QStringList>
#include <QDomDocument>
#include <QDomElement>

#include "track.h"
#include "GeoUtils.h"

namespace godwit
{

QString Track::mDateTimeFormat = "yyyy-MM-ddThh:mm:ssZ";

void Track::init(std::list<Point>& points, std::string name, QDateTime timestamp)
{
    mPoints = points;
    mName = name;
    mTimestamp = timestamp;

    auto delta = [](const Point& a, const Point& b)
    {
        return haversine(a.getLatitude(), a.getLongitude(), b.getLatitude(), b.getLongitude()) ;
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

Track::Track()
{}

Track::Track(std::list<Point>& points, std::string name, QDateTime timestamp)
{
    init(points, name, timestamp);
}

double Track::retrieveDoubleAttribute(const QDomElement& e, const QString& attr)
{
    double ret = 0.0;
    QString s = e.attribute(attr);

    bool conv;
    ret = s.toDouble(&conv);

    if(!conv)
    {
        qDebug() << "Conversion to double failed";
    }

    return ret;
}

double Track::retrieveDoubleSingleChild(const QDomElement& e, const QString& tag)
{
    double ret = 0.0;

    QDomNodeList nl = e.elementsByTagName(tag);
    if(nl.length() == 1)
    {
        QDomElement tmp = nl.at(0).toElement();
        if(!tmp.isNull())
        {
            auto x = tmp.text();
            bool conv;
            ret = x.toDouble(&conv);
            if(!conv)
            {
                qDebug() << "Conversion to double failed";
            }
        }
    }

    return ret;
}

QDateTime Track::retrieveQDateTimeSingleChild(const QDomElement& e, const QString& tag)
{
    QDateTime ret;

    QDomNodeList nl = e.elementsByTagName(tag);
    if(nl.length() == 1)
    {
        QDomElement tmp = nl.at(0).toElement();
        if(!tmp.isNull())
        {
            QString s = tmp.text();
            ret = QDateTime::fromString(s, mDateTimeFormat);
            if(ret.isNull() || !ret.isValid())
            {
                qDebug() << "Conversion to QDateTime failed";
            }
        }
    }

    return ret;
}

Track::Track(const QString& fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        throw (Track_creation_exception());
    }

    QDomDocument doc("gpx");
    if(!doc.setContent(&file))
    {
        file.close();
        throw (Track_creation_exception());
    }

    std::list<Point> l;

    QDomElement root = doc.documentElement();
    QDomNodeList trkpts = root.elementsByTagName("trkpt");
    for(int i = 0; i < trkpts.length(); i++)
    {
        QDomElement e = trkpts.at(i).toElement();
        if(!e.isNull())
        {
            double lat = retrieveDoubleAttribute(e, "lat");
            double lon = retrieveDoubleAttribute(e, "lon");
            double ele = retrieveDoubleSingleChild(e, "ele");
            // TODO int hearRate =
            QDateTime timestamp = retrieveQDateTimeSingleChild(e, "time");

            Point p(lat, lon, ele, 0, timestamp);
            l.push_back(p);
        }
    }

    file.close();

    init(l, "", QDateTime::currentDateTime());
}

}
