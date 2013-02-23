#ifndef EXTENDEDGEODATACOORDINATES_H
#define EXTENDEDGEODATACOORDINATES_H

#include <marble/GeoDataCoordinates.h>
#include <QDateTime>

using namespace Marble;

/*
 * Extends Marble::GeoDataCoordinates with:
 * - Timestamp
 * - HeartRate
 */

class ExtendedGeoDataCoordinates : public GeoDataCoordinates
{
public:
    ExtendedGeoDataCoordinates(const ExtendedGeoDataCoordinates& that)
        : GeoDataCoordinates(that)
    {
        mTimestamp = that.mTimestamp;
    }

    ExtendedGeoDataCoordinates(
            qreal lon,
            qreal lat,
            qreal alt = 0,
            GeoDataCoordinates::Unit unit = GeoDataCoordinates::Radian,
            int detail = 0,
            QDateTime timestamp = QDateTime::currentDateTime(),
            unsigned int heartRate = 0)
        : GeoDataCoordinates(lon, lat, alt, unit, detail),
          mTimestamp(timestamp),
          mHeartRate(heartRate)
    {
    }

    QDateTime timestamp() const
    {
        return mTimestamp;
    }

    unsigned int heartRate() const
    {
        return mHeartRate;
    }

private:
    QDateTime mTimestamp;
    unsigned int mHeartRate;
};

#endif // EXTENDEDGEODATACOORDINATES_H
