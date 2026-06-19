#ifndef RAYTRACER_CPP_CANVAS_H
#define RAYTRACER_CPP_CANVAS_H
#include <vector>

#include "raylib.h"
#include "Vec.h"


struct View {
    float x, y, d;
};

class Canvas {
public:
    std::vector<Color> pixels;
    int width, height;
    View view;

    Canvas(const int width, const int height, const View view):
    width(width), height(height), view(view)
    {
        pixels.resize(width * height, RAYWHITE);
    };

    void put_pixel(int x, int y, Color color);
    [[nodiscard]] Vec3 canvas_to_viewport(int x, int y) const;
};


#endif //RAYTRACER_CPP_CANVAS_H
