#pragma once

#include <iosfwd>

class Vec3 {
public:
    union {
        struct { double x, y, z; };
        struct { double r, g, b; };
    };

    Vec3(double x, double y, double z);
    explicit Vec3(double scalar);
    Vec3() = default;
    ~Vec3() = default;

    Vec3& operator+=(const Vec3& other);
    Vec3& operator-=(const Vec3& other);
    Vec3& operator*=(double scalar);
    Vec3& operator/=(double scalar);

    [[nodiscard]] double length() const;
    [[nodiscard]] double length_squared() const;
    [[nodiscard]] bool isZero() const;
    static Vec3 random();
    static Vec3 random(double min, double max);
    static Vec3 randomUnitVector();
    static Vec3 randomUnitVectorCourse();
    static Vec3 randomAlongNormal(const Vec3& normal);
    static Vec3 randomInUnitDisk();

    Vec3& normalizeSelf();
    [[nodiscard]] Vec3 normalize() const;
};

using Color = Vec3;
using Point3 = Vec3;

// Utils
Vec3 operator+(const Vec3& left, const Vec3& right);
Vec3 operator-(const Vec3& left, const Vec3& right);
Vec3 operator*(const Vec3& vec, double scalar);
Vec3 operator*(double scalar, const Vec3& vec);
Vec3 operator/(const Vec3& vec, double scalar);
Vec3 operator/(double scalar, const Vec3& vec);
Vec3 operator*(const Vec3& first, const Vec3& second);
Vec3 operator-(const Vec3& vec);
Vec3 cross(const Vec3& first, const Vec3& second);
double dot(const Vec3& first, const Vec3& second);
bool operator==(const Vec3& first, const Vec3& second);
bool operator!=(const Vec3& first, const Vec3& second);
std::ostream& operator<<(std::ostream& os, const Vec3& vec);