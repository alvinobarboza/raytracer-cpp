#ifndef RAYTRACER_CPP_CAMERA_H
#define RAYTRACER_CPP_CAMERA_H
#include "Vec.h"

class RayCamera {
    public:
    static inline float DefaultMoveSpeed = 4.0f;
    static inline float DefaultTurnSpeed = 70.0f;

    Vec3 position, direction, rotation;
    float moveSpeed, turnSpeed;

    RayCamera(
        const Vec3 position, const Vec3 direction, const Vec3 rotation,
        const float moveSpeed, const float turnSpeed):
    position {position}, direction {direction}, rotation {rotation}, moveSpeed {moveSpeed},
    turnSpeed {turnSpeed} {}

    void move_forward(float speed);
    void move_backward(float speed);
    void move_left(float speed);
    void move_right(float speed);
    void handle_input();
};

#endif //RAYTRACER_CPP_CAMERA_H
