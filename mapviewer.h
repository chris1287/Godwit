#ifndef MAPVIEWER_H
#define MAPVIEWER_H

#include <marble/MarbleWidget.h>
#include <marble/GeoDataLineString.h>
#include <marble/GeoDataCoordinates.h>

using namespace Marble;

class MapViewer : public MarbleWidget
{

public:
    virtual void customPaint(GeoPainter* painter);
    void updateTrackPoints(const QString& fileName);
    GeoDataCoordinates getLastPointLoaded();

private:
    GeoDataLineString mTrackPoints;
};

#endif // MAPVIEWER_H
