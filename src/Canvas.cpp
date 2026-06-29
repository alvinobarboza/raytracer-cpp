#include "Canvas.h"

void Canvas::put_pixel(const int x, const int y, const Color color)
{
    const int cX = width / 2 + x;
    const int cY = height / 2 - y;

    const int i = cY * width + cX;

    if (i < 0 || i >= pixels.size()) {
        return;
    }

    pixels[i] = color;
}

Vec3 Canvas::canvas_to_viewport(const int x, const int y) const
{
    return {
        (static_cast<float>(x) * view.x) / static_cast<float>(width),
        (static_cast<float>(y) * view.y) / static_cast<float>(height),
        view.d
    };
}