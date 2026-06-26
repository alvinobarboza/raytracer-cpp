#include "RayTracer.h"
#include "cmath"
#include "Maths.h"

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

Vec3 RayTracer::reflect_ray(const Vec3 &ray, const Vec3 &normal) {
    const float angle = ray.dot(normal);
    return normal * 2 * angle - ray;
}

float RayTracer::compute_light(const Vec3 &point, const Vec3 &normal, const Vec3 &objToCam, const int specular) const {
    float intensity = 0.0f;

    for (auto &light : this->lights) {
        if (light.type == LightType::AMBIENT_LIGHT) {
            intensity = light.intensity;
        } else {
            Vec3 lightDirection = light.direction;
            if (light.type == LightType::POINT_LIGHT) {
                lightDirection = light.position - point;
            }

            // Shadows
            if (auto [sphere, _] = this->closest_intersection(point, lightDirection, 0.001f); sphere.radius > 0) {
                continue;
            }

            // Diffuse
            if (const float angle = normal.dot(lightDirection); angle > 0) {
                const float normalLength = normal.length();
                const float lightDirectionLength = lightDirection.length();

                intensity += light.intensity * angle / (normalLength * lightDirectionLength);
            }

            // Specular
            if (specular != -1) {
                Vec3 reflected = reflect_ray(lightDirection, normal);
                if (const float angle = reflected.dot(objToCam); angle > 0) {
                    const float reflectedLength = reflected.length();
                    const float objToCamLength = objToCam.length();

                    intensity += std::pow(angle/(reflectedLength*objToCamLength), static_cast<float>(specular));
                }
            }
        }
    }

    if (intensity > 1.0f) {
        intensity = 1.0f;
    }

    return intensity;
}

Color RayTracer::sky_color(const Vec3 &ray) {
    const Vec3 up = Vec3::UP();
    const Vec3 rayNormalized = ray.normalize();

    const float angle = up.dot(rayNormalized);

    constexpr auto gray = GRAY;
    constexpr auto darkblue = Color(0, 40, 80, 255);

    const auto r = static_cast<unsigned char>(Math::lerp_to(gray.r, darkblue.r, angle));
    const auto g = static_cast<unsigned char>(Math::lerp_to(gray.g, darkblue.g, angle));
    const auto b = static_cast<unsigned char>(Math::lerp_to(gray.b, darkblue.b, angle));

    return {r, g, b, 255};
}

Color RayTracer::trace_ray(const Vec3 &origin, const Vec3 &ray, const float min_distance, const int bounce) const {
    auto [closes_sphere, closest_inter] = this->closest_intersection(origin, ray, min_distance);

    if (closes_sphere.radius == 0) {
        return sky_color(ray);
    }

    const Vec3 point = origin + ray * closest_inter;
    Vec3 normal = point - closes_sphere.center;

    normal = normal.normalize();
    const Vec3 objToCam = ray * -1;

    Color finalColor = closes_sphere.color;

    const float i = this->compute_light(point, normal, objToCam, closes_sphere.specularity);

    finalColor.r = static_cast<unsigned char>(static_cast<float>(finalColor.r) * i);
    finalColor.g = static_cast<unsigned char>(static_cast<float>(finalColor.g) * i);
    finalColor.b = static_cast<unsigned char>(static_cast<float>(finalColor.b) * i);

    if (bounce <= 0 || closes_sphere.reflectivity <= 0) {
        return finalColor;
    }

    const Vec3 reflected = reflect_ray(objToCam, normal);
    const Color reflectedColor = this->trace_ray(point, reflected, 0.001f, bounce-1);

    const float r = closes_sphere.reflectivity;

    finalColor.r = static_cast<unsigned char>(static_cast<float>(finalColor.r)*(1-r) + static_cast<float>(reflectedColor.r)*r);
    finalColor.g = static_cast<unsigned char>(static_cast<float>(finalColor.g)*(1-r) + static_cast<float>(reflectedColor.g)*r);
    finalColor.b = static_cast<unsigned char>(static_cast<float>(finalColor.b)*(1-r) + static_cast<float>(reflectedColor.b)*r);

    return finalColor;
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
                rayCorrectedDirection,
                this->canvas.view.d,
                this->max_bounce);

            this->canvas.put_pixel(x,y,color);
        }
    }
}
