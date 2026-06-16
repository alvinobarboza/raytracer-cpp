#include <iostream>
#include "raylib.h"

int main() {

    InitWindow(800, 480, "Hello raylib");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}