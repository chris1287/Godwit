#ifndef GPXPARSER_H
#define GPXPARSER_H

#include <QDomDocument>
#include <QDomElement>
#include <QFile>
#include <QDateTime>
#include <QDebug>
#include <marble/GeoDataLineString.h>

#include "extendedgeodatacoordinates.h"

using namespace Marble;

double retrieveDoubleAttribute(const QDomElement& e, const QString& attr)
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

double retrieveDoubleSingleChild(const QDomElement& e, const QString& tag)
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

QDateTime retrieveQDateTimeSingleChild(const QDomElement& e, const QString& tag, const QString& dateTimeFormat)
{
    QDateTime ret;

    QDomNodeList nl = e.elementsByTagName(tag);
    if(nl.length() == 1)
    {
        QDomElement tmp = nl.at(0).toElement();
        if(!tmp.isNull())
        {
            QString s = tmp.text();
            ret = QDateTime::fromString(s, dateTimeFormat);
            if(ret.isNull() || !ret.isValid())
            {
                qDebug() << "Conversion to QDateTime failed";
            }
        }
    }

    return ret;
}

bool parseGpxFile(const QString& fileName, GeoDataLineString& track, const QString& dateTimeFormat = "yyyy-MM-ddThh:mm:ssZ")
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Could not open " << fileName;
        return false;
    }

    QDomDocument doc("gpx");
    if(!doc.setContent(&file))
    {
        file.close();
        qDebug() << "Could not parse " << fileName;
        return false;
    }

    QDomElement root = doc.documentElement();
    QDomNodeList trkpts = root.elementsByTagName("trkpt");
    for(int i = 0; i < trkpts.length(); i++)
    {
        QDomElement e = trkpts.at(i).toElement();
        if(!e.isNull())
        {
            double lon = retrieveDoubleAttribute(e, "lon");
            double lat = retrieveDoubleAttribute(e, "lat");
            double ele = retrieveDoubleSingleChild(e, "ele");
            // TODO int hearRate =
            QDateTime timestamp = retrieveQDateTimeSingleChild(e, "time", dateTimeFormat);

            ExtendedGeoDataCoordinates p(lon, lat, ele, GeoDataCoordinates::Degree, 0, timestamp);
            track << p;
        }
    }

    file.close();

    return true;
}

#endif // GPXPARSER_H
