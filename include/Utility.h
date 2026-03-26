#pragma once

#include <random>

#include "Vec3.h"
#include "Interval.h"

inline constexpr double PI = 3.14159265358979323846;

inline double linearToGamma(const double linearComponent) {
    if (linearComponent > 0)
        return std::sqrt(linearComponent);
    return 0;
}

inline std::tuple<int, int, int> normalizeColor(const Vec3& color) {
    double r = color.r;
    double g = color.g;
    double b = color.b;

    // Apply a linear to gamma transform for gamma = 2
    r = linearToGamma(r);
    g = linearToGamma(g);
    b = linearToGamma(b);

    // Translate from real [0, 1] range to integer [0, 255] range
    static const Interval intensity(0.0, 0.9999);
    const int redByte   = static_cast<int>(256 * intensity.clamp(r));
    const int greenByte = static_cast<int>(256 * intensity.clamp(g));
    const int blueByte  = static_cast<int>(256 * intensity.clamp(b));

    return { redByte, greenByte, blueByte };
}

inline void writeColor(std::ostream& os, const Vec3& color) {
    double r = color.r;
    double g = color.g;
    double b = color.b;

    // Apply a linear to gamma transform for gamma = 2
    r = linearToGamma(r);
    g = linearToGamma(g);
    b = linearToGamma(b);

    // Translate from real [0, 1] range to integer [0, 255] range
    static const Interval intensity(0.0, 0.9999);
    const int redByte   = static_cast<int>(256 * intensity.clamp(r));
    const int greenByte = static_cast<int>(256 * intensity.clamp(g));
    const int blueByte  = static_cast<int>(256 * intensity.clamp(b));
    os << redByte << ' ' << greenByte << ' ' << blueByte << '\n';
}

inline double degreesToRadians(const double degrees) {
    return PI * degrees / 180;
}

inline double randomDouble() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;

    return distribution(generator);
}

inline double randomDouble(const double min, const double max) {
    return min + (max - min) * randomDouble();
}

inline double randomDouble(const Interval interval) {
    return randomDouble(interval.min, interval.max);
}

inline Vec3 reflect(const Vec3& vector, const Vec3& normal) {
    return (vector - 2 * dot(vector, normal) * normal).normalize();
}

inline Vec3 refract(const Vec3& vector, const Vec3& normal, const double refractiveIndicesRatio) {
    const double cosTheta = std::fmin(dot(-vector, normal), 1.0);
    const Vec3 resultPerpendicular = refractiveIndicesRatio * (vector + cosTheta * normal);
    const Vec3 resultParallel = -std::sqrt(std::fabs(1.0 - resultPerpendicular.length_squared())) * normal;

    return (resultPerpendicular + resultParallel).normalize();
}