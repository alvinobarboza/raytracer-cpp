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
    int pool_size;
    int tile_size;;
    float max_bounce_distance;
    std::vector<Light> lights;
    std::vector<Sphere> spheres;
    ThreadPool pool;
public:
    RayCamera &camera;
    Canvas canvas;

    RayTracer(
        RayCamera &camera,
        Canvas canvas,
        const int max_bounce,
        const float max_bounce_distance,
        const int pool_size,
        const int tile_size) :
    max_bounce(max_bounce),
    max_bounce_distance(max_bounce_distance),
    pool(pool_size),
    pool_size(pool_size),
    camera(camera),
    canvas(std::move(canvas)),
    tile_size(tile_size){
    };

    void add_light(const Light &light);
    void add_sphere(const Sphere &sphere);
    void compute_rays();
private:
    [[nodiscard]] Vec3 trace_ray(Vec3 origin, Vec3 _ray, float min_distance, int bounce) const;
    [[nodiscard]] std::pair<Sphere, float> closest_intersection(Vec3 origin, Vec3 ray, float min_distance) const;
    [[nodiscard]] float compute_light(Vec3 point, Vec3 normal, Vec3 objToCam, int specular ) const;
    [[nodiscard]] static Vec3 reflect_ray(Vec3 ray, Vec3 normal);
    [[nodiscard]] static Vec3 sky_color(Vec3 ray);
    [[nodiscard]] static float ray_angle_from_normal(Vec3 ray, Vec3 normal);
    [[nodiscard]] static Vec3 refract_ray(Vec3 ray, Vec3 normal, float rIndex);
};


#endif //RAYTRACER_CPP_RAYTRACER_H
