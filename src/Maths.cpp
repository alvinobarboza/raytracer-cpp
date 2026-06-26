#include "Maths.h"

#include <cmath>

float Math::lerp_to(const float a, const float b, const float t) {
    const float r = clamp(t , 0.0f, 1.0f);
    return a + r * (b - a);
}

float Math::clamp(const float x, const float min, const float max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

