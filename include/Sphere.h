#ifndef RAYTRACER_CPP_SPHERE_H
#define RAYTRACER_CPP_SPHERE_H
#include "raylib.h"
#include "Vec.h"

class Sphere {
    public:
    Vec3 center;
    Color color;
    float radius;
    int specularity;
    float reflectivity;
    float refractionIndex;
    float opacity;

    Sphere(
        Vec3 center, Color color,
        float radius, int specularity,
        float reflectivity, float refractionIndex, float opacity) :
center(center), color(color), radius(radius), specularity(specularity),
reflectivity(reflectivity), refractionIndex(refractionIndex), opacity(opacity) {}
};

#endif //RAYTRACER_CPP_SPHERE_H
