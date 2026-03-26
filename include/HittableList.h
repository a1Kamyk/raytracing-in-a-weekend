#pragma once


#include "Hittable.h"
#include "Ray.h"
#include "Interval.h"

#include <vector>
#include <memory>

using std::unique_ptr;
using std::make_unique;

class HittableList final : public Hittable {
public:
    std::vector<unique_ptr<Hittable>> objects;

    HittableList() = default;
    ~HittableList() override = default;

    void clear();
    void add(unique_ptr<Hittable> hittable);

    bool hit(const Ray& ray, Interval rayT, HitRecord& hitRecord) const override;
};