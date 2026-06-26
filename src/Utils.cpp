#include "Utils.h"
#include "Maths.h"

Color Utils::vec3_to_color(const Vec3 &vec) {
    return {
        static_cast<unsigned char>(Math::clamp(vec.x, 0.0f, 1.0f) * 255.0f),
        static_cast<unsigned char>(Math::clamp(vec.y, 0.0f, 1.0f) * 255.0f),
        static_cast<unsigned char>(Math::clamp(vec.z, 0.0f, 1.0f) * 255.0f),
        255
    };
}

Vec3 Utils::color_to_vec3(const Color &color) {
    return {
        static_cast<float>(color.r) / 255.0f,
        static_cast<float>(color.g) / 255.0f,
        static_cast<float>(color.b) / 255.0f
    };
}