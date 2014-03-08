#include <Math/Math.h>

template <>
void Math::SquareMatrix<float, Rt::u1, 1>::loadIdentity()
{
    static const float identity[1][1] = {{ 1.0f }};
    memcpy(this->matrix, identity, sizeof(identity));
}

template <>
void Math::SquareMatrix<double, Rt::u1, 1>::loadIdentity()
{
    static const double identity[1][1] = {{ 1.0 }};
    memcpy(this->matrix, identity, sizeof(identity));
}

template <>
void Math::transposeSquareMatrixInPlace<float, Rt::u1, 1>(float matrix[1 * 1])
{}

template <>
void Math::transposeSquareMatrix<float, Rt::u1, 1>(const float matrix[1 * 1], float transpose[1 * 1])
{}

template <>
void Math::transposeSquareMatrixInPlace<double, Rt::u1, 1>(double matrix[1 * 1])
{}

template <>
void Math::transposeSquareMatrix<double, Rt::u1, 1>(const double matrix[1 * 1], double transpose[1 * 1])
{}

template <>
bool Math::inverseMatrix<float, Rt::u1, 1>(MatrixLayout layout, const float matrix[1 * 1], float inverse[1 * 1]) {
    inverse[0] = 1.0f / matrix[0];
    return true;
}

template <>
bool Math::inverseMatrix<double, Rt::u1, 1>(MatrixLayout layout, const double matrix[1 * 1], double inverse[1 * 1]) {
    inverse[0] = 1.0 / matrix[0];
    return true;
}
