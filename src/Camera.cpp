#include "Camera.h"

void RayCamera::move_forward(const float speed) {
    const Vec3 dir = this->direction.rotate_xyz(this->rotation);
    const Vec3 normal = dir.normal();
    this->position += normal * speed;
}

void RayCamera::move_backward(const float speed) {
    this->move_forward(-speed);
}

void RayCamera::move_left(const float speed) {
    const Vec3 dir = this->direction.rotate_xyz(this->rotation);
    const Vec3 sideDir = dir.cross(Vec3::UP());

    const Vec3 normalSideDir = sideDir.normal();
    this->position += normalSideDir * speed;
}

void RayCamera::move_right(const float speed) {
    this->move_left(-speed);
}
