#include "HittableList.h"

void HittableList::clear() {
    objects.clear();
}

void HittableList::add(unique_ptr<Hittable> hittable) {
    objects.push_back(std::move(hittable));
}

bool HittableList::hit(const Ray& ray, const Interval rayT, HitRecord& hitRecord) const {
    HitRecord tempRecord{};
    bool hitAny = false;
    double closestHit = rayT.max;

    for (const auto& object : objects) {
        if (object->hit(ray, Interval(rayT.min, closestHit), tempRecord)) {
            hitAny = true;
            closestHit = tempRecord.t;
        }
    }

    hitRecord = tempRecord;
    return hitAny;
}