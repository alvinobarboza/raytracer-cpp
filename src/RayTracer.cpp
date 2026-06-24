#include "RayTracer.h"

void RayTracer::add_light(const Light &light) {
    this->lights.push_back(light);
}

void RayTracer::add_sphere(const Sphere &sphere)
{
    this->spheres.push_back(sphere);
}

std::pair<Sphere, float> RayTracer::closest_intersection(
    const Vec3 &origin, const Vec3 &ray, const float min_distance) const
{
    float closest_intersection = this->max_bounce_distance;
    Sphere sphere;

    for (auto &s : this->spheres) {
        auto [t1, t2] = s.intersect(origin, ray, this->max_bounce_distance);

        if (t1 < closest_intersection && min_distance < t1 && t1 < this->max_bounce_distance) {
            closest_intersection = t1;
            sphere = s;
        }

        if (t2 < closest_intersection && min_distance < t2 && t2 < this->max_bounce_distance) {
            closest_intersection = t2;
            sphere = s;
        }
    }

    return {sphere, closest_intersection};
}

Color RayTracer::trace_ray(const Vec3 &origin, const Vec3 &ray, const float min_distance) const {
    auto [closes_sphere, closest_inter] = this->closest_intersection(origin, ray, min_distance);

    if (closes_sphere.radius == 0) return GRAY;

    return closes_sphere.color;
}

void RayTracer::compute_rays() {
    const int startX = -this->canvas.width / 2;
    const int startY = -this->canvas.height / 2;
    const int endX = this->canvas.width / 2;
    const int endY = this->canvas.height / 2;

    for (int x = startX; x < endX; x++) {
        for (int y = startY; y < endY; y++) {
            auto rayDirection = this->canvas.canvas_to_viewport(x, y);
            auto rayCorrectedDirection = rayDirection * this->camera.rotationMatrix;

            const auto color = this->trace_ray(
                this->camera.position,
                rayCorrectedDirection, this->canvas.view.d);

            this->canvas.put_pixel(x,y,color);
        }
    }
}
