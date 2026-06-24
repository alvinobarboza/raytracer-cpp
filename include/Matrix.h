#ifndef RAYTRACER_CPP_MATRIX_H
#define RAYTRACER_CPP_MATRIX_H
#include <array>

class Matrix3x3 {
    public:
    std::array<float, 9> data = {
        1,0,0,
        0,1,0,
        0,0,1,
    };
    Matrix3x3()= default;
    Matrix3x3(
        const float m00, const float m01, const float m02,
        const float m10, const float m11, const float m12,
        const float m20, const float m21, const float m22)
    {
        data[0] = m00; data[1] = m01; data[2] = m02;
        data[3] = m10; data[4] = m11; data[5] = m12;
        data[6] = m20; data[7] = m21; data[8] = m22;
    }
};


#endif //RAYTRACER_CPP_MATRIX_H
