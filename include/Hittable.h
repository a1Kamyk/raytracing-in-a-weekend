#pragma once

#include <memory>

#include "Vec3.h"
#include "Ray.h"
#include "Interval.h"

class Material;

class HitRecord {
public:
    Point3 point;
    Vec3 normal;
    std::shared_ptr<Material> material;
    double t;
    bool frontFace;

    void setFaceNormal(const Ray& ray, const Vec3& outwardNormal);
};

class Hittable {
public:
    virtual ~Hittable() = default;
    [[nodiscard]] virtual auto hit(const Ray& ray,
                                   Interval rayT,
                                   HitRecord& hitRecord) const -> bool = 0;
};