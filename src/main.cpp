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

    auto ray_camera = RayCamera(
        Vec3::ZERO(),
        Vec3::FORWARD(),
        Vec3::ZERO(),
        RayCamera::DefaultMoveSpeed,
        RayCamera::DefaultTurnSpeed
    );

    auto view_canvas = Canvas(
        screenWidth, screenHeight,
        View{1, static_cast<float>(screenHeight) / static_cast<float>(screenWidth), 1}
    );

    auto ray_tracer = RayTracer(max_bounces, max_distance);
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

    const int posX = static_cast<int>(screenWidth / 2.0f - static_cast<float>(canvasTexture.width )/ 2.0f);
    const int posY = static_cast<int>(screenHeight / 2.0f - static_cast<float>(canvasTexture.height) / 2.0f);

    constexpr int startX = -screenWidth / 2;
    constexpr int startY = -screenHeight / 2;
    constexpr int endX = screenWidth / 2;
    constexpr int endY = screenHeight / 2;

    while (!WindowShouldClose())
    {
        ray_camera.handle_input();

        for (int x = startX; x < endX; x++) {
            for (int y = startY; y < endY; y++) {
                auto rayDirection = view_canvas.canvas_to_viewport(x, y);
                auto rayCorrectedDirection = rayDirection.rotate_xyz(ray_camera.rotation);

                const auto color = ray_tracer.trace_ray(
                    ray_camera.position,
                    rayCorrectedDirection, view_canvas.view.d);

                view_canvas.put_pixel(x,y,color);
            }
        }

        UpdateTexture(canvasTexture, view_canvas.pixels.data());

        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawTexture(canvasTexture, posX, posY, WHITE);
            DrawFPS(10, 10);

            DrawText(
                TextFormat("Cam-> \nX:%01f \nY:%01f \nZ:%01f",
                    ray_camera.position.x, ray_camera.position.y, ray_camera.position.z),
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