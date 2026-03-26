#pragma once

#include "Vec3.h"

class Ray {
public:
    Ray() = default;
    Ray(const Point3& origin, const Vec3& direction);
    Ray(const Point3& origin, const Vec3& direction, double time);

    [[nodiscard]] const Point3& origin() const { return m_origin; }
    [[nodiscard]] const Vec3& direction() const { return m_direction; }
    [[nodiscard]] double time() const { return m_time; }

    [[nodiscard]] Point3 at(double t) const;
    [[nodiscard]] Vec3 unitDirection() const;
private:
    Point3 m_origin{};
    Vec3 m_direction{};
    double m_time{};
};