#include "Sphere.h"

#include <algorithm>
#include <cmath>
#include <ostream>

Sphere::Sphere(const Point3& center, const double radius, const std::shared_ptr<Material>& material) :
    m_center(center, Vec3{0,0,0}),  m_radius(std::fmax(0, radius)), m_material(material) {}

Sphere::Sphere(const Point3& centerStart, const Point3& centerEnd, const double radius, const std::shared_ptr<Material>& material) :
    m_center(centerStart, centerEnd - centerStart), m_radius(std::fmax(0, radius)), m_material(material) {}

bool Sphere::hit(const Ray& ray, const Interval rayT, HitRecord& hitRecord) const {
    const Point3 currentCenter = m_center.at(ray.time());
    const Vec3 oc = currentCenter - ray.origin();
    const double h = dot(oc, ray.direction());
    const double c = oc.length_squared() - m_radius * m_radius;
    const double discriminant = h * h - c;

    if (discriminant < 0) return false;

    const double sqrtDisc = std::sqrt(discriminant);

    // Finding nearest root withing [rayTmin, rayTmax]
    double root = h - sqrtDisc;
    if (!rayT.surrounds(root)) {
        root = h + sqrtDisc;
        if (!rayT.surrounds(root)) return false;
    }

    hitRecord.t = root;
    hitRecord.point = ray.at(root);
    const Vec3 outwardNormal = (hitRecord.point - currentCenter) / m_radius;
    hitRecord.setFaceNormal(ray, outwardNormal);
    hitRecord.material = m_material;

    return true;
}