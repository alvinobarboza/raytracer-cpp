#ifndef RAYTRACER_CPP_VEC_H
#define RAYTRACER_CPP_VEC_H
#include <iostream>

#include "Matrix.h"

class Vec3 {
public:
    float x, y, z;

    Vec3(const float x, const float y, const float z): x(x), y(y), z(z) {}

    [[nodiscard]] float dot(const Vec3 &other) const;
    [[nodiscard]] float length_squared() const;
    [[nodiscard]] float length() const;
    [[nodiscard]] Vec3 normal() const;

    Vec3 operator*(float scalar) const;
    Vec3 operator*(const Vec3 &scalar) const;
    Vec3 operator*(const Matrix3x3 &matrix) const;
    Vec3 operator+(const Vec3 &vector) const;

    Vec3 rotate_xyz(const Vec3 &angle) const;

    friend std::ostream& operator<<(std::ostream &os, const Vec3 &vector);
};

#endif //RAYTRACER_CPP_VEC_H
