#include <marble/GeoPainter.h>
#include <QDebug>

#include "gpxParser.h"
#include "mapviewer.h"

void MapViewer::customPaint(GeoPainter* painter)
{
    QPen pen(Qt::green);
    pen.setWidth(4);

    painter->setPen(pen);
    painter->drawPolyline(mTrackPoints);
}

void MapViewer::updateTrackPoints(const QString &fileName)
{
    if(parseGpxFile(fileName, mTrackPoints))
    {
        centerOn(mTrackPoints.latLonAltBox());
    }
    else
    {
        qDebug() << "Could not update track using " << fileName;
    }
}

GeoDataCoordinates MapViewer::getLastPointLoaded()
{
    if(mTrackPoints.size() > 0)
        return mTrackPoints.first();

    return GeoDataCoordinates();
}

