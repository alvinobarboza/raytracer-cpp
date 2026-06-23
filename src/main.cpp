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

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        ray_camera.handle_input();

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