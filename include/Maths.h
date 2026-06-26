#ifndef RAYTRACER_CPP_CONSTANTS_H
#define RAYTRACER_CPP_CONSTANTS_H
#include "Vec.h"

namespace Math {
    constexpr float _PI = 3.14159265358979323846;
    constexpr float TAU = 2.0 * _PI;
    constexpr float DEG_TO_RAD = TAU / 360.0f;
    constexpr float RAD_TO_DEG = 360.0f / TAU;
    float lerp_to(float a, float b, float t);
    float fresnel_schlick(const Vec3 &incidence, const Vec3 &normal, float refractive_index);
    float clamp(float x, float min, float max);
}

#endif //RAYTRACER_CPP_CONSTANTS_H
