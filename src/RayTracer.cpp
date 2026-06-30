#include "RayTracer.h"
#include "cmath"
#include "Maths.h"

void RayTracer::add_light(const Light &light) {
    lights.push_back(light);
}

void RayTracer::add_sphere(const Sphere &sphere)
{
    spheres.push_back(sphere);
}

std::pair<Sphere, float> RayTracer::closest_intersection(
    const Vec3 origin, const Vec3 ray, const float min_distance) const
{
    float closest_intersection = max_bounce_distance;
    Sphere sphere;

    for (auto &s : spheres) {
        auto [t1, t2] = s.intersect(origin, ray, max_bounce_distance);

        if (t1 < closest_intersection && min_distance < t1 && t1 < max_bounce_distance) {
            closest_intersection = t1;
            sphere = s;
        }

        if (t2 < closest_intersection && min_distance < t2 && t2 < max_bounce_distance) {
            closest_intersection = t2;
            sphere = s;
        }
    }

    return {sphere, closest_intersection};
}

Vec3 RayTracer::reflect_ray(const Vec3 ray, const Vec3 normal) {
    const float angle = ray.dot(normal);
    return normal * 2 * angle - ray;
}

float RayTracer::compute_light(const Vec3 point, const Vec3 normal, const Vec3 objToCam, const int specular) const {
    float intensity = 0.0f;

    for (auto &light : lights) {
        if (light.type == LightType::AMBIENT_LIGHT) {
            intensity = light.intensity;
        } else {
            Vec3 lightDirection = light.direction;
            if (light.type == LightType::POINT_LIGHT) {
                lightDirection = light.position - point;
            }

            // Shadows
            if (auto [sphere, _] = closest_intersection(point, lightDirection, 0.001f); sphere.radius > 0) {
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

Vec3 RayTracer::sky_color(const Vec3 ray) {
    const Vec3 up = Vec3::UP();
    const Vec3 rayNormalized = ray.normalize();

    const float angle = up.dot(rayNormalized);

    const auto gray = Utils::color_to_vec3(GRAY);
    const auto blue = Utils::color_to_vec3(DARKBLUE);
    const auto darkblue = Vec3(0, 40.0f / 255.0f, 80 / 255.0f);

    if (angle < 0.5f) {
        return gray.lerp_to(blue, angle * 2);
    }

    return blue.lerp_to(darkblue, (angle * 2.0f) - 1.0f);
}

float RayTracer::ray_angle_from_normal(const Vec3 ray, const Vec3 normal) {
    const float dot = ray.dot(normal);
    const float rayLength = ray.length();
    const float normalLength = normal.length();

    return std::acos(dot / (rayLength * normalLength));
}

// Refraction: source https://devforum.roblox.com/t/what-is-the-formula-for-refraction/2171867/17
// i = ray
// t = refracted ray
// n = surface normal
// n1 = refractive index of the first medium
// n2 = refractive index of the second medium
// u = ratio of refraction indices, u = n1 / n2
// d = (-n) . i
// . = dot product
// Formula:
// t = i * u + n * (u * d - sqrt(1-u²*(1-d²)))
Vec3 RayTracer::refract_ray(const Vec3 ray, const Vec3 normal, const float rIndex) {
    const Vec3 i = ray;
    const Vec3 n = normal;
    constexpr float n1 = 1.0f;
    const float n2 = rIndex;
    const float u = n1/n2;
    const auto d = (n*-1).dot(i);

    const auto delta = std::sqrt(1-(u*u)*(1-(d*d)));

    const auto sqrtSum = n * (u*d - delta);
    const auto t = i*u + sqrtSum;
    return t;
}

// TODO: create ray class to cache length and normalized vector
Vec3 RayTracer::trace_ray(const Vec3 origin, const Vec3 _ray, const float min_distance, const int bounce) const {
    const Vec3 ray = _ray.normalize();

    auto [closes_sphere, closest_inter] = closest_intersection(origin, ray, min_distance);

    if (closes_sphere.radius == 0) {
        return sky_color(ray);
    }

    const Vec3 point = origin + ray * closest_inter;
    Vec3 normal = point - closes_sphere.center;

    normal = normal.normalize();
    const Vec3 objToCam = ray * -1;

    Vec3 finalColor = closes_sphere.color;

    const float intensity = compute_light(point, normal, objToCam, closes_sphere.specularity);

    finalColor = finalColor * intensity;

    if (bounce <= 0) {
        return finalColor;
    }

    if (closes_sphere.opacity > 0.0f) {
        const auto refraction = refract_ray(ray, normal, closes_sphere.refractionIndex);
        const Vec3 transparent = trace_ray(point, refraction, min_distance, bounce-1);
        finalColor = finalColor.lerp_to(transparent, closes_sphere.opacity);
    }

    if (closes_sphere.reflectivity <= 0) {
        return finalColor;
    }

    const Vec3 reflected = reflect_ray(objToCam, normal);
    const Vec3 reflectedColor = trace_ray(point, reflected, 0.001f, bounce-1);

    const float r = closes_sphere.reflectivity;
    finalColor = finalColor.lerp_to(reflectedColor, r);

    return finalColor;
}

void RayTracer::compute_rays() {
    // Just testing
    if (IsKeyDown(KEY_UP)) {
        spheres.at(spheres.size()-2).center.z += 1 * GetFrameTime();
    }
    if (IsKeyDown(KEY_DOWN)) {
        spheres.at(spheres.size()-2).center.z -= 1 * GetFrameTime();
    }
    if (IsKeyDown(KEY_LEFT)) {
        spheres.at(spheres.size()-2).center.x -= 1 * GetFrameTime();
    }
    if (IsKeyDown(KEY_RIGHT)) {
        spheres.at(spheres.size()-2).center.x += 1 * GetFrameTime();
    }
    // Just testing

    const int startX = -canvas.width / 2;
    const int startY = -canvas.height / 2;
    const int endX = canvas.width / 2;
    const int endY = canvas.height / 2;

    for (int tileY = startY; tileY < endY; tileY += tile_size) {
        for (int tileX = startX; tileX < endX; tileX += tile_size) {
            pool.enqueue([this, tileX, tileY, endX, endY ] {
                for (int y = 0; y < tile_size && tileY + y < endY; y++) {
                    for (int x = 0; x < tile_size && tileX + x < endX; x++) {
                        const int posX = tileX + x;
                        const int posY = tileY + y;

                        const auto rayDirection = canvas.canvas_to_viewport(posX,  posY);
                        const auto rayCorrectedDirection = rayDirection * camera.rotationMatrix;

                        const auto color = trace_ray(
                            camera.position,
                            rayCorrectedDirection,
                            canvas.view.d,
                            max_bounce);

                        canvas.put_pixel(posX, posY, Utils::vec3_to_color(color));
                    }
                }
            });
        }
    }

    pool.wait();
}
