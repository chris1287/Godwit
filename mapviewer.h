#ifndef MAPVIEWER_H
#define MAPVIEWER_H

#include <marble/MarbleWidget.h>
#include <marble/GeoDataLineString.h>
#include <marble/GeoDataCoordinates.h>
#include "point.h"
#include "track.h"

using namespace Marble;
using namespace godwit;

class MapViewer : public MarbleWidget
{

public:
    virtual void customPaint(GeoPainter* painter);
    void updateTrackPoints(Track& t);
    GeoDataCoordinates getLastPointLoaded();

private:
    GeoDataLineString mTrackPoints;
};

#endif // MAPVIEWER_H
