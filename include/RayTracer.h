#ifndef RAYTRACER_CPP_RAYTRACER_H
#define RAYTRACER_CPP_RAYTRACER_H
#include <utility>
#include <vector>

#include "Camera.h"
#include "Canvas.h"
#include "Lights.h"
#include "Sphere.h"
#include "ThreadPool.h"

class RayTracer {
    int max_bounce;
    float max_bounce_distance;
    std::vector<Light> lights;
    std::vector<Sphere> spheres;
    ThreadPool pool;
public:
    RayCamera camera;
    Canvas canvas;

    RayTracer(const RayCamera &camera, Canvas canvas,const int max_bounce, const float max_bounce_distance) : max_bounce(
        max_bounce), max_bounce_distance(max_bounce_distance), pool(4), camera(camera), canvas(std::move(canvas)) {
    };

    void add_light(const Light &light);
    void add_sphere(const Sphere &sphere);
    void compute_rays();
private:
    [[nodiscard]] Vec3 trace_ray(const Vec3 &origin, const Vec3 &_ray, float min_distance, int bounce) const;
    [[nodiscard]] std::pair<Sphere, float> closest_intersection(const Vec3 &origin, const Vec3 &ray, float min_distance) const;
    [[nodiscard]] float compute_light(const Vec3 &point, const Vec3 &normal, const Vec3 &objToCam, int specular ) const;
    [[nodiscard]] static Vec3 reflect_ray(const Vec3 &ray, const Vec3 &normal);
    [[nodiscard]] static Vec3 sky_color(const Vec3 &ray);
    [[nodiscard]] static float ray_angle_from_normal(const Vec3 &ray, const Vec3 &normal);
    [[nodiscard]] static Vec3 refract_ray(const Vec3 &ray, const Vec3 &normal, float rIndex);
};


#endif //RAYTRACER_CPP_RAYTRACER_H
