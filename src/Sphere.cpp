#include "Sphere.h"

#include <cmath>

std::pair<float, float> Sphere::intersect(
    const Vec3 &rayOrigin, const Vec3 &rayDir, const float maxDist) const
{
    const float r = this->radius;

    const Vec3 co = rayOrigin - this->center;

    const float a = rayDir.dot(rayDir);
    const float b = 2 * co.dot(rayDir);
    const float c = co.dot(co) - (r * r);

    const float delta =  b * b - 4 * a * c;
    if (delta <= 0) {
        return {maxDist, maxDist};
    }

    float t1 = (-b + std::sqrt(delta)) / (2 * a);
    float t2 = (-b - std::sqrt(delta)) / (2 * a);

    return {t1, t2};
}
