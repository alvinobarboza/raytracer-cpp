#include "Canvas.h"

void Canvas::put_pixel(const int x, const int y, const Color color) {
    const int cX = this->width / 2 + x;
    const int cY = this->height / 2 - y;

    const int i = cY * this->width + cX;

    if (i < 0 || i >= this->pixels.size()) {
        return;
    }

    this->pixels[i] = color;
}

Vec3 Canvas::canvas_to_viewport(const int x, const int y) const {
    return {
        x * this->view.x / this->width,
        y * this->view.y / this->height,
        this->view.d
    };
}