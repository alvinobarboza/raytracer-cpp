#include <iostream>
#include "raylib.h"

#include "Vec.h"

int main() {
    const Matrix3x3 mat3 = {
        2, 3, 4,
        5, 6, 7,
        8, 9, 10
    };

    const Vec3 n1 {10, 10, 10};
    const Vec3 n2 {20, 20, 20};

    const Vec3 v1 {2, 3, 4};
    const Vec3 v2 {3, 5, 6};

    std::cout << v1.cross(v2) << std::endl;
    std::cout << v1 * mat3 << std::endl;
    std::cout << Vec3::UP() << std::endl;

    const Vec3 n3 = n1 * n2;


    const float dotV = n3.length_squared();

    std::cout << n3 * mat3 << n3 << dotV << std::endl;

    const Vec3 n4 {10, 0, 0};
    const Vec3 rotated = n4.rotate_y(90);
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