#include "Camera.h"
#include "raylib.h"

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

void RayCamera::handle_input() {
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
