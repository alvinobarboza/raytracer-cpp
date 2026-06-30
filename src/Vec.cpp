#include "Vec.h"
#include <cmath>

#include "Maths.h"

float Vec3::dot(const Vec3 &other) const
{
    return x * other.x + y * other.y + z * other.z;
}

float Vec3::length_squared() const
{
    return x * x + y * y + z * z;
}

float Vec3::length() const
{
    return std::sqrt(length_squared());
}

Vec3 Vec3::normalize() const
{
    const float normal = length();
    if (normal == 0) return {0,0,0};

    return {
        x / normal,
        y / normal,
        z / normal
    };
}

Vec3 Vec3::cross(const Vec3 &other) const
{
    return {
        y*other.z - z*other.y,
        z*other.x - x*other.z,
        x*other.y - y*other.x,
    };
}

Vec3 Vec3::lerp_to(const Vec3 &other, const float ratio) const
{
    return {
        Math::lerp_to(x,other.x,ratio),
        Math::lerp_to(y,other.y,ratio),
        Math::lerp_to(z,other.z,ratio),
    };
}

Vec3 Vec3::operator*(const float scalar) const
{
    return {
        x * scalar,
        y * scalar,
        z * scalar
    };
}

Vec3 Vec3::operator*(const Vec3 &scalar) const
{
    return {
        x * scalar.x,
        y * scalar.y,
        z * scalar.z
    };
}

Vec3 Vec3::operator+(const Vec3 &vector) const
{
    return {
        x + vector.x,
        y + vector.y,
        z + vector.z
    };
}

Vec3 Vec3::operator-(const Vec3 &vector) const
{
    return {
        x - vector.x,
        y - vector.y,
        z - vector.z
    };
}

void Vec3::operator+=(const Vec3 &vector)
{
    x += vector.x;
    y += vector.y;
    z += vector.z;
}

Vec3 Vec3::operator*(const Matrix3x3 &matrix) const
{
    return {
        x * matrix.data[0] + y * matrix.data[1] + z * matrix.data[2],
        x * matrix.data[3] + y * matrix.data[4] + z * matrix.data[5],
        x * matrix.data[6] + y * matrix.data[7] + z * matrix.data[8]
    };
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