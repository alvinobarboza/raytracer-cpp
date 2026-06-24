#include "Vec.h"
#include <cmath>

#include "Constants.h"

float Vec3::dot(const Vec3 &other) const
{
    return this->x * other.x + this->y * other.y + this->z * other.z;
}

float Vec3::length_squared() const
{
    return this->x * this->x + this->y * this->y + this->z * this->z;
}

float Vec3::length() const
{
    return std::sqrt(this->length_squared());
}

Vec3 Vec3::normal() const
{
    const float normal = this->length();
    if (normal == 0) return {0,0,0};

    return {
        this->x / normal,
        this->y / normal,
        this->z / normal
    };
}

Vec3 Vec3::cross(const Vec3 &other) const
{
    return {
        this->y*other.z - this->z*other.y,
        this->z*other.x - this->x*other.z,
        this->x*other.y - this->y*other.x,
    };
}

Vec3 Vec3::operator*(const float scalar) const
{
    return {
        this->x * scalar,
        this->y * scalar,
        this->z * scalar
    };
}

Vec3 Vec3::operator*(const Vec3 &scalar) const
{
    return {
        this->x * scalar.x,
        this->y * scalar.y,
        this->z * scalar.z
    };
}

Vec3 Vec3::operator+(const Vec3 &vector) const
{
    return {
        this->x + vector.x,
        this->y + vector.y,
        this->z + vector.z
    };
}

Vec3 Vec3::operator-(const Vec3 &vector) const
{
    return {
        this->x - vector.x,
        this->y - vector.y,
        this->z - vector.z
    };
}

void Vec3::operator+=(const Vec3 &vector)
{
    this->x += vector.x;
    this->y += vector.y;
    this->z += vector.z;
}

Vec3 Vec3::operator*(const Matrix3x3 &matrix) const
{
    return {
        this->x * matrix.data[0] + this->y * matrix.data[1] + this->z * matrix.data[2],
        this->x * matrix.data[3] + this->y * matrix.data[4] + this->z * matrix.data[5],
        this->x * matrix.data[6] + this->y * matrix.data[7] + this->z * matrix.data[8]
    };
}

Vec3 Vec3::rotate_x(const float angle) const
{
    return this->rotate_xyz({angle, 0,0});
}

Vec3 Vec3::rotate_y(const float angle) const
{
    return this->rotate_xyz({0, angle,0});
}

Vec3 Vec3::rotate_z(const float angle) const
{
    return this->rotate_xyz({0, 0,angle});
}

Vec3 Vec3::rotate_xyz(const Vec3 &angle) const
{
    const float cosa = std::cos(angle.x * -Math::DEG_TO_RAD);
    const float sina = std::sin(angle.x * -Math::DEG_TO_RAD);

    const float cosb = std::cos(angle.y * -Math::DEG_TO_RAD);
    const float sinb = std::sin(angle.y * -Math::DEG_TO_RAD);

    const float cosga = std::cos(angle.z * -Math::DEG_TO_RAD);
    const float singa = std::sin(angle.z * -Math::DEG_TO_RAD);

    const Matrix3x3 matrix = {
        cosb * cosga, sina*sinb*cosga - cosa*singa, cosa*sinb*cosga + sina*singa,
        cosb * singa, sina*sinb*singa + cosa*cosga, cosa*sinb*singa - sina*cosga,
        -sinb, sina * cosb, cosa * cosb
    };

    return *this * matrix;
}

std::ostream& operator<<(std::ostream &os, const Vec3 &vector)
{
    os << "(x:" << vector.x << ", y:" << vector.y << ", z:" << vector.z << ")";
    return os;
}

Vec3 Vec3::UP()
{
    return {0,1,0};
};

Vec3 Vec3::DOWN()
{
    return {0,-1,0};
};

Vec3 Vec3::FORWARD()
{
    return {0,0,1};
};

Vec3 Vec3::BACKWARD()
{
    return {0,0,-1};
};

Vec3 Vec3::LEFT()
{
    return {-1,0,0};
};

Vec3 Vec3::RIGHT()
{
    return {1,0,0};
};

Vec3 Vec3::ZERO()
{
    return {0,0,0};
};