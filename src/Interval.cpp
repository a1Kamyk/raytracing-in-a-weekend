#include "Interval.h"

#include <limits>

constexpr double infinity = std::numeric_limits<double>::infinity();

const Interval Interval::empty = Interval(+infinity, -infinity);
const Interval Interval::universe = Interval(-infinity, infinity);

Interval::Interval() :
    min(+infinity), max(-infinity) {}

Interval::Interval(const double _min, const double _max) :
    min(_min), max(_max) {}

double Interval::size() const {
    return max - min;
}

double Interval::clamp(const double x) const {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

bool Interval::contains(const double x) const {
    return x >= min && x <= max;
}

bool Interval::surrounds(const double x) const {
    return x > min && x < max;
}