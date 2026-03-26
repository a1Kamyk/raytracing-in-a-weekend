#include "Plane.h"

#include <cmath>

Plane::Plane(const Point3& point, const Vec3& normal, const std::shared_ptr<Material>& material) :
    m_point(point), m_normal(normal.normalize()), m_material(material) {}

bool Plane::hit(const Ray& ray, const Interval rayT, HitRecord& hitRecord) const {
    // (rayO + t * rayD - planeP) * planeNormal = 0
    const double denominator = dot(m_normal, ray.direction());
    if (std::fabs(denominator) < 1e-8) return false;
    const double t = dot(m_normal, m_point - ray.origin()) / denominator;

    // Checking if t lies in range given
    if (!rayT.surrounds(t)) return false;

    hitRecord.t = t;
    hitRecord.point = ray.at(t);
    hitRecord.setFaceNormal(ray, m_normal);
    hitRecord.material = m_material;

    return true;
}
