#include <iostream>
#include "raylib.h"

#include "Vec.h"

int main() {

    const Vec3 n1 {10, 10, 10};
    const Vec3 n2 {20, 20, 20};

    const Vec3 n3 = n1 * n2;
    const Matrix3x3 mat3 = {
        2, 3, 4,
        5, 6, 7,
        9, 8, 10
    };

    const float dotV = n3.length_squared();

    std::cout << n3 * mat3 << n3 << dotV << std::endl;

    const Vec3 n4 {10, 0, 0};
    const Vec3 rotated = n4.rotate_xyz({0,90,0});
    std::cout << rotated << std::endl;

    std::cout << rotated + n3 << std::endl;

    InitWindow(800, 480, "Hello raylib");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
        break;
    }

    CloseWindow();

    return 0;
}