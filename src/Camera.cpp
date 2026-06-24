#include "Camera.h"

#include <cmath>

#include "Constants.h"
#include "raylib.h"

void RayCamera::update_camera_transform() {
    const float cosa = std::cos(this->rotation.x * -Math::DEG_TO_RAD);
    const float sina = std::sin(this->rotation.x * -Math::DEG_TO_RAD);

    const float cosb = std::cos(this->rotation.y * -Math::DEG_TO_RAD);
    const float sinb = std::sin(this->rotation.y * -Math::DEG_TO_RAD);

    const float cosga = std::cos(this->rotation.z * -Math::DEG_TO_RAD);
    const float singa = std::sin(this->rotation.z * -Math::DEG_TO_RAD);

    this->rotationMatrix.data[0] = cosb * cosga;
    this->rotationMatrix.data[1] = sina*sinb*cosga - cosa*singa;
    this->rotationMatrix.data[2] = cosa*sinb*cosga + sina*singa;

    this->rotationMatrix.data[3] = cosb * singa;
    this->rotationMatrix.data[4] = sina*sinb*singa + cosa*cosga;
    this->rotationMatrix.data[5] = cosa*sinb*singa - sina*cosga;

    this->rotationMatrix.data[6] = -sinb;
    this->rotationMatrix.data[7] = sina * cosb;
    this->rotationMatrix.data[8] = cosa * cosb;
}

void RayCamera::move_forward(const float speed)
{
    const Vec3 dir = this->direction.rotate_xyz(this->rotation);
    const Vec3 normal = dir.normal();
    this->position += normal * speed;
}

void RayCamera::move_backward(const float speed)
{
    this->move_forward(-speed);
}

void RayCamera::move_left(const float speed)
{
    const Vec3 dir = this->direction.rotate_xyz(this->rotation);
    const Vec3 sideDir = dir.cross(Vec3::UP());

    const Vec3 normalSideDir = sideDir.normal();
    this->position += normalSideDir * speed;
}

void RayCamera::move_right(const float speed)
{
    this->move_left(-speed);
}

void RayCamera::handle_input()
{
    if (IsKeyDown(KEY_W)) {
        this->move_forward(this->moveSpeed * GetFrameTime());
    }
    if (IsKeyDown(KEY_S)) {
        this->move_backward(this->moveSpeed * GetFrameTime());
    }
    if (IsKeyDown(KEY_A)) {
        this->move_left(this->moveSpeed * GetFrameTime());
    }
    if (IsKeyDown(KEY_D)) {
        this->move_right(this->moveSpeed * GetFrameTime());
    }
    if (IsKeyDown(KEY_SPACE)) {
        this->position.y += this->moveSpeed * GetFrameTime();
    }
    if (IsKeyDown(KEY_LEFT_CONTROL)) {
        this->position.y -= this->moveSpeed * GetFrameTime();
    }

    if (IsKeyDown(KEY_RIGHT)) {
        this->rotation.y -= this->turnSpeed * GetFrameTime();
    }
    if (IsKeyDown(KEY_LEFT)) {
        this->rotation.y += this->turnSpeed * GetFrameTime();
    }
    if (IsKeyDown(KEY_UP)) {
        this->rotation.x += this->turnSpeed * GetFrameTime();
        if (this->rotation.x >= 90) {
            this->rotation.x = 89;
        }
    }
    if (IsKeyDown(KEY_DOWN) && this->rotation.x < 90){
        this->rotation.x -= this->turnSpeed * GetFrameTime();
        if (this->rotation.x <= -90 ){
            this->rotation.x = -89;
        }
    }
}
