#ifndef TRACKLAYER_H
#define TRACKLAYER_H

#include <QStringList>
#include <marble/LayerInterface.h>
#include <marble/MarbleWidget.h>
#include <marble/GeoDataLineString.h>
#include <marble/GeoDataCoordinates.h>

using namespace Marble;

class TrackLayer : public LayerInterface
{
public:
    TrackLayer(MarbleWidget *parent);

public:
    // Inherited from LayerInterface
    virtual QStringList renderPosition() const;
    virtual bool render(GeoPainter *painter, ViewportParams *viewport, const QString &renderPos, GeoSceneLayer *layer);

public:
    void updateTrackPoints(const QString& fileName);
    GeoDataCoordinates getLastPointLoaded();

private:
    MarbleWidget *mParent;
    GeoDataLineString mTrackPoints;
};

#endif // TRACKLAYER_H
