#ifndef RAYTRACER_CPP_SPHERE_H
#define RAYTRACER_CPP_SPHERE_H
#include "raylib.h"
#include "Utils.h"
#include "Vec.h"

class Sphere {
    public:
    Vec3 center;
    Vec3 color;
    float radius;
    int specularity;
    float reflectivity{};
    float refractionIndex;
    float opacity;

    Sphere(): center(Vec3::ZERO()), color(Vec3::ZERO()) {
        radius = 0.0f;
        specularity = 0.0f;
        refractionIndex = 0.0f;
        opacity = 0.0f;
    };

    Sphere(
        const Vec3 center, const Color color,
        const float radius, const int specularity,
        const float reflectivity, const float refractionIndex, const float opacity) :
        center(center), color(Utils::color_to_vec3(color)), radius(radius), specularity(specularity),
        reflectivity(reflectivity), refractionIndex(refractionIndex), opacity(opacity) {}

    [[nodiscard]] std::pair<float,float> intersect(const Vec3 &rayOrigin, const Vec3 &rayDir, float maxDist) const;
};

#endif //RAYTRACER_CPP_SPHERE_H
