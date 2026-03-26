#pragma once

#include "Hittable.h"

class Plane final : public Hittable {
public:
    Plane() = default;
    Plane(const Point3& point, const Vec3& normal, const std::shared_ptr<Material>& material);

    bool hit(const Ray& ray, Interval rayT, HitRecord& hitRecord) const override;
private:
    Point3 m_point{};
    Vec3 m_normal{};
    std::shared_ptr<Material> m_material{};
};
