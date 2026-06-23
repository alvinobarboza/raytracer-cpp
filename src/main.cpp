#include <iostream>

#include "Camera.h"
#include "Canvas.h"
#include "raylib.h"
#include "RayTracer.h"
#include "Vec.h"

// void draw_raytracer_camera(const RayCamera &camera) {
//     const Vector3 position = { camera.position.x, camera.position.y, -camera.position.z };
//     const Vec3 endDir = camera.direction.rotate_xyz(camera.rotation);
//     const Vector3 direction = { endDir.x, endDir.y, -endDir.z };
//     const Vector3 endPos = {position.x+direction.x*2, position.y+direction.y*2, position.z+direction.z*2};
//
//     DrawLine3D(position, endPos, DARKGREEN);
//     DrawSphere(position, 1.0f, RED);
//     DrawSphereWires(position, 1.1f, 12, 12, MAROON);
// }


int main() {
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 450;
    constexpr int max_bounces = 5;
    constexpr float max_distance = 1000000000.0f;

    InitWindow(screenWidth, screenHeight, "Camera movement");
    SetTargetFPS(60);

    const auto ray_camera = RayCamera(
        Vec3::ZERO(),
        Vec3::FORWARD(),
        Vec3::ZERO(),
        RayCamera::DefaultMoveSpeed,
        RayCamera::DefaultTurnSpeed
    );

    const auto view_canvas = Canvas(
        screenWidth, screenHeight,
        View{1, static_cast<float>(screenHeight) / static_cast<float>(screenWidth), 1}
    );

    auto ray_tracer = RayTracer(ray_camera, view_canvas, max_bounces, max_distance);
    ray_tracer.add_sphere(Sphere(
        Vec3(0,-1,3),RED,1,500,0.2,0,0
        ));
    ray_tracer.add_sphere(Sphere(
        Vec3(2,0,4),BLUE,1,500,0.001,0,0
        ));
    ray_tracer.add_sphere(Sphere(
        Vec3(-2,0,4),GREEN,1,10,0.1,0,0
        ));
    ray_tracer.add_sphere(Sphere(
        Vec3(-0.5,0,2),BLUE,0.4f,200,0.2,1.33,0.9
        ));
    ray_tracer.add_sphere(Sphere(
        Vec3(0,-501,0),DARKGREEN,500,200,0.1,0,0
    ));

    const auto tempImageTexture = GenImageColor(screenWidth, screenHeight, WHITE);
    const auto canvasTexture = LoadTextureFromImage(tempImageTexture);
    UnloadImage(tempImageTexture);

    // TODO = I don't remember why I did this in the go version
    constexpr int posX = 0;
    constexpr int posY = 0;

    while (!WindowShouldClose())
    {
        ray_tracer.camera.handle_input();
        ray_tracer.compute_rays();

        UpdateTexture(canvasTexture, ray_tracer.canvas.pixels.data());

        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawTexture(canvasTexture, posX, posY, WHITE);
            DrawFPS(10, 10);

            DrawText(
                TextFormat("Cam-> \nX:%01f \nY:%01f \nZ:%01f",
                    ray_tracer.camera.position.x, ray_tracer.camera.position.y, ray_tracer.camera.position.z),
                10, 30, 20, WHITE);
            DrawText("Move: A/W/S/D\nControl Camera: UP/DOWN/LEFT/RIGHT",10, 120, 20, WHITE);
            DrawText("I'm a bit too lazy to make \nit work with the mouse...",10, 160, 10, WHITE);
        EndDrawing();

        if (IsKeyDown(KEY_Q)) {
            break;
        }
    }

    CloseWindow();

    return 0;
}