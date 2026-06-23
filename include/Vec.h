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
    [[nodiscard]] Vec3 cross(const Vec3 &other) const;

    Vec3 operator*(float scalar) const;
    Vec3 operator*(const Vec3 &scalar) const;
    Vec3 operator*(const Matrix3x3 &matrix) const;
    Vec3 operator+(const Vec3 &vector) const;
    Vec3 operator-(const Vec3 &vector) const;
    void operator+=(const Vec3 &vector);

    [[nodiscard]] Vec3 rotate_x(float angle) const;
    [[nodiscard]] Vec3 rotate_y(float angle) const;
    [[nodiscard]] Vec3 rotate_z(float angle) const;
    [[nodiscard]] Vec3 rotate_xyz(const Vec3 &angle) const;

    friend std::ostream& operator<<(std::ostream &os, const Vec3 &vector);

    static Vec3 UP();
    static Vec3 DOWN();
    static Vec3 FORWARD();
    static Vec3 BACKWARD();
    static Vec3 LEFT();
    static Vec3 RIGHT();
    static Vec3 ZERO();
};

#endif //RAYTRACER_CPP_VEC_H
