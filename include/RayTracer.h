//
// Created by alvino.barboza on 23/06/2026.
//

#ifndef RAYTRACER_CPP_RAYTRACER_H
#define RAYTRACER_CPP_RAYTRACER_H
#include <vector>

#include "Lights.h"
#include "Sphere.h"

class RayTracer {
public:
    int max_bounce;
    float max_bounce_distance;
    std::vector<Light> lights;
    std::vector<Sphere> spheres;

    RayTracer(const int max_bounce, const float max_bounce_distance):
    max_bounce(max_bounce), max_bounce_distance(max_bounce_distance) {};

    void add_light(const Light &light);
    void add_sphere(const Sphere &sphere);
    [[nodiscard]] Color trace_ray(
        const Vec3 &origin, const Vec3 &ray,
        float min_distance
        ) const;

private:
    [[nodiscard]] std::pair<Sphere, float> closest_intersection(const Vec3 &origin, const Vec3 &ray, float min_distance) const;
};


#endif //RAYTRACER_CPP_RAYTRACER_H
