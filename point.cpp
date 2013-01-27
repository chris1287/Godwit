#include "point.h"

namespace godwit
{

Point::Point
(
        double latitude = 0.0,
        double longitude = 0.0,
        double altitude = 0.0,
        int heartRate = 0,
        QDateTime timestamp = QDateTime::currentDateTime()
)
{
    if
    (
            latitude < 0 ||
            longitude < 0 ||
            altitude < 0 ||
            heartRate < 0
    )
    {
        throw( Point_creation_exception() );
    }

    mLatitude = latitude;
    mLongitude = longitude;
    mAltitude = altitude;
    mHeartRate = heartRate;
    mTimestamp = timestamp;
}

bool Point::equals(const Point &that) const
{
    // TODO maybe check for a less stronger equality
    // TODO maybe use a policy in order to define what equality is
    return
            mLatitude == that.mLatitude &&
            mLongitude == that.mLongitude &&
            mAltitude == that.mAltitude &&
            mHeartRate == that.mHeartRate &&
            mTimestamp == that.mTimestamp;
}

bool Point::operator ==(const Point &that) const
{
    return this->equals(that);
}

bool Point::operator !=(const Point &that) const
{
    return !this->equals(that);
}

}
