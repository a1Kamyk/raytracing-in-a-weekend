#pragma once

class Interval {
public:
    double min, max;

    Interval();
    Interval(double _min, double _max);

    [[nodiscard]] double size() const;
    [[nodiscard]] double clamp(double x) const;
    [[nodiscard]] bool contains(double x) const;
    [[nodiscard]] bool surrounds(double x) const;

    static const Interval empty, universe;
};