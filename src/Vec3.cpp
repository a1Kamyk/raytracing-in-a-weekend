#include "Vec3.h"

#include <cmath>
#include <iostream>

#include "Utility.h"

Vec3::Vec3(const double x,const double y,const double z) :
    x{x}, y{y}, z{z} {}

Vec3::Vec3(const double scalar) :
    x{scalar}, y{scalar}, z{scalar} {}

Vec3& Vec3::operator+=(const Vec3& other) {
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    return *this;
}

Vec3& Vec3::operator-=(const Vec3& other) {
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    return *this;
}

Vec3& Vec3::operator*=(const double scalar) {
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
    return *this;
}

Vec3& Vec3::operator/=(const double scalar) {
    this->x /= scalar;
    this->y /= scalar;
    this->z /= scalar;
    return *this;
}

double Vec3::length() const {
    return std::sqrt(x*x + y*y + z*z);
}

double Vec3::length_squared() const {
    return x*x + y*y + z*z;
}

bool Vec3::isZero() const {
    constexpr double eps = 1e-8;
    return (std::fabs(x) < eps && std::fabs(y) < eps && std::fabs(z) < eps);
}

Vec3 Vec3::random() {
    return {
        randomDouble(),
        randomDouble(),
        randomDouble()
    };
}

Vec3 Vec3::random(const double min, const double max) {
    return {
        randomDouble(min, max),
        randomDouble(min, max),
        randomDouble(min, max)
    };
}

Vec3 Vec3::randomUnitVector() {
    const double theta = randomDouble(0, 2 * PI);
    const double z = randomDouble(-1, 1);
    const double r = sqrt(1 - z*z);
    const double x = r * std::cos(theta);
    const double y = r * std::sin(theta);

    return {x, y, z};
}

Vec3 Vec3::randomUnitVectorCourse() {
    while (true) {
        const auto p = Vec3::random(-1, 1);
        if (const double lensq = p.length_squared(); 1e-160 < lensq && lensq <= 1) {
            return p / sqrt(lensq);
        }
    }
}

Vec3 Vec3::randomAlongNormal(const Vec3& normal) {
    if (const Vec3 random = randomUnitVector(); dot(normal, random) > 0.0)
        return random;
    else
        return -random;
}

Vec3 Vec3::randomInUnitDisk() {
    const double r = std::sqrt(randomDouble(0, 1));
    const double theta = randomDouble(0, 2 * PI);

    const double x = r * std::cos(theta);
    const double y = r * std::sin(theta);

    return {
        x,
        y,
        0
    };
}

Vec3& Vec3::normalizeSelf() {
    const double len = this->length();
    x /= len;
    y /= len;
    z /= len;

    return *this;
}

Vec3 Vec3::normalize() const {
    const double len = this->length();
    return {
        x / len,
        y / len,
        z / len
    };
}

Vec3 operator+(const Vec3& left, const Vec3& right) {
    return {
        left.x + right.x,
        left.y + right.y,
        left.z + right.z
    };
}

Vec3 operator-(const Vec3& left, const Vec3& right) {
    return {
        left.x - right.x,
        left.y - right.y,
        left.z - right.z
    };
}

Vec3 operator*(const Vec3& vec, const double scalar) {
    return {
        vec.x * scalar,
        vec.y * scalar,
        vec.z * scalar
    };
}

Vec3 operator*(const double scalar, const Vec3& vec) {
    return vec * scalar;
}

Vec3 operator/(const Vec3& vec, const double scalar) {
    return {
        vec.x / scalar,
        vec.y / scalar,
        vec.z / scalar
    };
}

Vec3 operator/(const double scalar, const Vec3& vec) {
    return vec * scalar;
}

Vec3 operator*(const Vec3& first, const Vec3& second) {
    return{
        first.x * second.x,
        first.y * second.y,
        first.z * second.z
    };
}

Vec3 operator-(const Vec3& vec) {
    return {
        -vec.x,
        -vec.y,
        -vec.z
    };
}

Vec3 cross(const Vec3& first, const Vec3& second) {
    return {
        first.y * second.z - first.z * second.y,
        first.z * second.x - first.x * second.z,
        first.x * second.y - first.y * second.x
    };
}

double dot(const Vec3& first, const Vec3& second) {
    return first.x * second.x +
           first.y * second.y +
           first.z * second.z;
}

bool operator==(const Vec3& first, const Vec3& second) {
    return (first.x == second.x &&
            first.y == second.y &&
            first.z == second.z);
}

bool operator!=(const Vec3& first, const Vec3& second) {
    return !(first == second);
}

std::ostream& operator<<(std::ostream& os, const Vec3& vec) {
    return os << vec.x << ' '
              << vec.y << ' '
              << vec.z;
}