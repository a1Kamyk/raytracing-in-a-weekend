#pragma once

#include "Hittable.h"

class Sphere final : public Hittable {
public:
    Sphere() = default;
    // Stationary
    Sphere(const Point3& center, double radius, const std::shared_ptr<Material>& material);
    // Moving
    Sphere(const Point3& centerStart, const Point3& centerEnd, double radius, const std::shared_ptr<Material>& material);

    bool hit(const Ray& ray, Interval rayT, HitRecord& hitRecord) const override;
private:
    Ray m_center{};
    double m_radius{};
    std::shared_ptr<Material> m_material{};
};