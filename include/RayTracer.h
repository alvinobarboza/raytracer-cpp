//
// Created by alvino.barboza on 23/06/2026.
//

#ifndef RAYTRACER_CPP_RAYTRACER_H
#define RAYTRACER_CPP_RAYTRACER_H
#include <utility>
#include <vector>

#include "Camera.h"
#include "Canvas.h"
#include "Lights.h"
#include "Sphere.h"

class RayTracer {
    int max_bounce;
    float max_bounce_distance;
    std::vector<Light> lights;
    std::vector<Sphere> spheres;
public:
    RayCamera camera;
    Canvas canvas;

    RayTracer(const RayCamera &camera, Canvas canvas,const int max_bounce, const float max_bounce_distance):
    max_bounce(max_bounce), max_bounce_distance(max_bounce_distance), camera(camera), canvas(std::move(canvas)) {};

    void add_light(const Light &light);
    void add_sphere(const Sphere &sphere);
    void compute_rays();
private:
    [[nodiscard]] Color trace_ray(
        const Vec3 &origin, const Vec3 &ray,
        float min_distance
    ) const;
    [[nodiscard]] std::pair<Sphere, float> closest_intersection(const Vec3 &origin, const Vec3 &ray, float min_distance) const;
};


#endif //RAYTRACER_CPP_RAYTRACER_H
