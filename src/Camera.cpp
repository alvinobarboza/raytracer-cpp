#include "Camera.h"

#include <cmath>

#include "Maths.h"
#include "raylib.h"

void RayCamera::update_camera_transform() {
    const float cosa = std::cos(rotation.x * -Math::DEG_TO_RAD);
    const float sina = std::sin(rotation.x * -Math::DEG_TO_RAD);

    const float cosb = std::cos(rotation.y * -Math::DEG_TO_RAD);
    const float sinb = std::sin(rotation.y * -Math::DEG_TO_RAD);

    const float cosga = std::cos(rotation.z * -Math::DEG_TO_RAD);
    const float singa = std::sin(rotation.z * -Math::DEG_TO_RAD);

    rotationMatrix.data[0] = cosb * cosga;
    rotationMatrix.data[1] = sina*sinb*cosga - cosa*singa;
    rotationMatrix.data[2] = cosa*sinb*cosga + sina*singa;

    rotationMatrix.data[3] = cosb * singa;
    rotationMatrix.data[4] = sina*sinb*singa + cosa*cosga;
    rotationMatrix.data[5] = cosa*sinb*singa - sina*cosga;

    rotationMatrix.data[6] = -sinb;
    rotationMatrix.data[7] = sina * cosb;
    rotationMatrix.data[8] = cosa * cosb;
}

void RayCamera::move_forward(const float speed)
{
    const Vec3 dir = direction.rotate_xyz(rotation);
    const Vec3 normal = dir.normalize();
    position += normal * speed;
}

void RayCamera::move_backward(const float speed)
{
    move_forward(-speed);
}

void RayCamera::move_left(const float speed)
{
    const Vec3 dir = direction.rotate_xyz(rotation);
    const Vec3 sideDir = dir.cross(Vec3::UP());

    const Vec3 normalSideDir = sideDir.normalize();
    position += normalSideDir * speed;
}

void RayCamera::move_right(const float speed)
{
    move_left(-speed);
}

void RayCamera::move_view(const float x, const float y)
{
    rotation.x -= turnSpeed * y * GetFrameTime();
    rotation.y -= turnSpeed * x * GetFrameTime();

    if (rotation.x > 88) {
        rotation.x = 88;
    }
    if (rotation.x < -88) {
        rotation.x = -88;
    }

    update_camera_transform();
}

void RayCamera::handle_input()
{
    if (IsKeyDown(KEY_W)) {
        move_forward(moveSpeed * GetFrameTime());
    }
    if (IsKeyDown(KEY_S)) {
        move_backward(moveSpeed * GetFrameTime());
    }
    if (IsKeyDown(KEY_A)) {
        move_left(moveSpeed * GetFrameTime());
    }
    if (IsKeyDown(KEY_D)) {
        move_right(moveSpeed * GetFrameTime());
    }
    if (IsKeyDown(KEY_SPACE)) {
        position.y += moveSpeed * GetFrameTime();
    }
    if (IsKeyDown(KEY_LEFT_CONTROL)) {
        position.y -= moveSpeed * GetFrameTime();
    }

    // Update camera view/rotation

    if (IsKeyPressed(KEY_TAB)) {
        viewLocked = !viewLocked;
        if (viewLocked) {
            EnableCursor();
        }else {
            DisableCursor();
        }
    }

    if (!viewLocked) {
        if (auto [x, y] = GetMouseDelta(); x != 0 || y != 0 ) {
            move_view(x, y);
        }
    }
}
