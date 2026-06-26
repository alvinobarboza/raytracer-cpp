#ifndef RAYTRACER_CPP_UTILS_H
#define RAYTRACER_CPP_UTILS_H
#include "raylib.h"
#include "Vec.h"

namespace Utils {
    Color vec3_to_color(const Vec3 &vec);
    Vec3 color_to_vec3(const Color &color);
}

#endif //RAYTRACER_CPP_UTILS_H
