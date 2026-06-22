#ifndef RAYTRACER_CPP_CAMERA_H
#define RAYTRACER_CPP_CAMERA_H
#include "Vec.h"

class RayCamera {
    public:
    Vec3 position, direction, rotation;

    RayCamera(const Vec3 position, const Vec3 direction, const Vec3 rotation):
    position {position}, direction {direction}, rotation {rotation} {};

    void move_forward(float speed);
    void move_backward(float speed);
    void move_left(float speed);
    void move_right(float speed);
};

#endif //RAYTRACER_CPP_CAMERA_H
