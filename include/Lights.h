#ifndef RAYTRACER_CPP_LIGHTS_H
#define RAYTRACER_CPP_LIGHTS_H
#include "Vec.h"

enum class LightType {
    DIRECTIONAL_LIGHT,
    POINT_LIGHT,
    AMBIENT_LIGHT,
};

class Light {
    public:
    LightType type;
    float intensity;
    Vec3 direction;
    Vec3 position;

    Light();
    Light(const LightType type, const float intensity, const Vec3 position, const Vec3 direction):
    type {type}, intensity {intensity}, position {position}, direction {direction} {};
};

#endif //RAYTRACER_CPP_LIGHTS_H
