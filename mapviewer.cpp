#include "mapviewer.h"

#include "marble/GeoPainter.h"
#include <list>
#include <QDebug>

void MapViewer::customPaint(GeoPainter* painter)
{
    QPen pen(Qt::green);
    pen.setWidth(4);

    painter->setPen(pen);
    painter->drawPolyline(mTrackPoints);
}

void MapViewer::updateTrackPoints(Track &t)
{
    std::list<Point> points = t.getPoints();

    mTrackPoints.clear();

    for(auto i : points)
    {
        GeoDataCoordinates p(i.getLongitude(), i.getLatitude(), i.getAltitude(), GeoDataCoordinates::Degree);
        mTrackPoints << p;
    }

    Point i = t.getStart();
    GeoDataCoordinates p(i.getLongitude(), i.getLatitude(), i.getAltitude(), GeoDataCoordinates::Degree);
    centerOn(p);
}
