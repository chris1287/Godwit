#include <QDebug>
#include <marble/GeoPainter.h>

#include "tracklayer.h"
#include "gpxParser.h"

TrackLayer::TrackLayer(MarbleWidget *parent)
    : mParent(parent)
{
}

QStringList TrackLayer::renderPosition() const
{
    // Possible Values:
    //  "NONE"
    //  "STARS"
    //  "BEHIND_TARGET"
    //  "SURFACE"
    //  "HOVERS_ABOVE_SURFACE"
    //  "ATMOSPHERE"
    //  "ORBIT"
    //  "ALWAYS_ON_TOP"
    //  "FLOAT_ITEM"
    //  "USER_TOOLS"

    return QStringList() << "ALWAYS_ON_TOP";
}

bool TrackLayer::render(GeoPainter *painter, ViewportParams *viewport, const QString &renderPos, GeoSceneLayer *layer)
{
    QPen pen(Qt::green);
    pen.setWidth(4);

    painter->setPen(pen);
    painter->drawPolyline(mTrackPoints);

    return true;
}

void TrackLayer::updateTrackPoints(const QString &fileName)
{
    if(parseGpxFile(fileName, mTrackPoints))
    {
        mParent->centerOn(mTrackPoints.latLonAltBox());
    }
    else
    {
        qDebug() << "Could not update track using " << fileName;
    }
}

GeoDataCoordinates TrackLayer::getLastPointLoaded()
{
    if(mTrackPoints.size() > 0)
        return mTrackPoints.first();

    return GeoDataCoordinates();
}


