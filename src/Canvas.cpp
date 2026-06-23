#include "Canvas.h"

void Canvas::put_pixel(const int x, const int y, const Color color)
{
    const int cX = this->width / 2 + x;
    const int cY = this->height / 2 - y;

    const int i = cY * this->width + cX;

    if (i < 0 || i >= this->pixels.size()) {
        return;
    }

    this->pixels[i] = color;
}

Vec3 Canvas::canvas_to_viewport(const int x, const int y) const
{
    return {
        (static_cast<float>(x) * this->view.x) / static_cast<float>(this->width),
        (static_cast<float>(y) * this->view.y) / static_cast<float>(this->height),
        this->view.d
    };
}