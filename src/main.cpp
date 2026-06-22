#include <iostream>

#include "Camera.h"
#include "raylib.h"

#include "Vec.h"

void draw_raytracer_camera(const RayCamera &camera) {
    const Vector3 position = { camera.position.x, camera.position.y, -camera.position.z };
    const Vec3 endDir = camera.direction.rotate_xyz(camera.rotation);
    const Vector3 direction = { endDir.x, endDir.y, -endDir.z };
    const Vector3 endPos = {position.x+direction.x*2, position.y+direction.y*2, position.z+direction.z*2};

    DrawLine3D(position, endPos, DARKGREEN);
    DrawSphere(position, 1.0f, RED);
    DrawSphereWires(position, 1.1f, 12, 12, MAROON);
}

void input_handler(RayCamera &camera) {
    if (IsKeyDown(KEY_W)) {
        camera.move_forward(camera.moveSpeed * GetFrameTime());
    }
    if (IsKeyDown(KEY_S)) {
        camera.move_backward(camera.moveSpeed * GetFrameTime());
    }
    if (IsKeyDown(KEY_A)) {
        camera.move_left(camera.moveSpeed * GetFrameTime());
    }
    if (IsKeyDown(KEY_D)) {
        camera.move_right(camera.moveSpeed * GetFrameTime());
    }
    if (IsKeyDown(KEY_SPACE)) {
        camera.position.y += camera.moveSpeed * GetFrameTime();
    }
    if (IsKeyDown(KEY_LEFT_CONTROL)) {
        camera.position.y -= camera.moveSpeed * GetFrameTime();
    }

    if (IsKeyDown(KEY_RIGHT)) {
        camera.rotation.y -= camera.turnSpeed * GetFrameTime();
    }
    if (IsKeyDown(KEY_LEFT)) {
        camera.rotation.y += camera.turnSpeed * GetFrameTime();
    }
    if (IsKeyDown(KEY_UP)) {
        camera.rotation.x += camera.turnSpeed * GetFrameTime();
        if (camera.rotation.x >= 90) {
            camera.rotation.x = 89;
        }
    }
    if (IsKeyDown(KEY_DOWN) && camera.rotation.x < 90){
        camera.rotation.x -= camera.turnSpeed * GetFrameTime();
        if (camera.rotation.x <= -90 ){
            camera.rotation.x = -89;
        }
    }
}

int main() {
    RayCamera ray_camera = RayCamera(
        Vec3::ZERO(),
        Vec3::FORWARD(),
        Vec3::ZERO(),
        RayCamera::DefaultMoveSpeed,
        RayCamera::DefaultTurnSpeed
    );

    constexpr int screenWidth = 800;
    constexpr int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Camera movement");

    Camera3D camera = {};
    camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };  // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        input_handler(ray_camera);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(camera);
                draw_raytracer_camera(ray_camera);
                DrawGrid(10, 1.0f);
            EndMode3D();
            DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}