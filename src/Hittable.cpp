#include "Hittable.h"

void HitRecord::setFaceNormal(const Ray& ray, const Vec3& outwardNormal) {
    const double dotProduct = dot(ray.direction(), outwardNormal);
    // dotProduct < 0 if outwardNormal and ray point in the "opposite" direction
    // If ray points against the normal then we hit the front face
    frontFace = dotProduct < 0;
    normal = frontFace ? outwardNormal : -outwardNormal;
}
