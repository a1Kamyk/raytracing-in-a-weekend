#include "Ray.h"

Ray::Ray(const Point3& origin, const Vec3& direction) :
    m_origin(origin), m_direction(direction) {}

Ray::Ray(const Point3& origin, const Vec3& direction, const double time) :
    m_origin(origin), m_direction(direction), m_time(time) {}

Point3 Ray::at(const double t) const {
    return m_origin + m_direction * t;
}

Vec3 Ray::unitDirection() const {
    return m_direction.normalize();
}
