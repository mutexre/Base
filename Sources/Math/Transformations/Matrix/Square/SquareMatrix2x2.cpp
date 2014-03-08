#include <math.h>
#include <Math/Math.h>

template <>
void Math::SquareMatrix<float, Rt::u1, 2>::loadIdentity()
{
    static const float identity[2][2] = {
        { 1.0f, 0.0f },
        { 0.0f, 1.0f }
    };
    memcpy(this->matrix, identity, sizeof(identity));
}

template <>
void Math::SquareMatrix<double, Rt::u1, 2>::loadIdentity()
{
    static const double identity[2][2] = {
        { 1.0, 0.0 },
        { 0.0, 1.0 }
    };
    memcpy(this->matrix, identity, sizeof(identity));
}

template <>
void Math::transposeSquareMatrixInPlace<float, Rt::u1, 2>(float matrix[])
{
    float tmp = matrix[1];
    matrix[1] = matrix[2];
    matrix[2] = tmp;
}

template <>
void Math::transposeSquareMatrix<float, Rt::u1, 2>(const float matrix[], float transpose[])
{
    transpose[0] = matrix[0];
    transpose[1] = matrix[2];
    transpose[2] = matrix[1];
    transpose[3] = matrix[3];
}

template <>
void Math::transposeSquareMatrixInPlace<double, Rt::u1, 2>(double matrix[])
{
    double tmp = matrix[1];
    matrix[1] = matrix[2];
    matrix[2] = tmp;
}

template <>
void Math::transposeSquareMatrix<double, Rt::u1, 2>(const double matrix[], double transpose[]) {
    transpose[0] = matrix[0];
    transpose[1] = matrix[2];
    transpose[2] = matrix[1];
    transpose[3] = matrix[3];
}

template <>
bool Math::inverseMatrix<float, Rt::u1, 2>(MatrixLayout layout, const float matrix[], float inverse[]) {
    float det = matrix[0 * 2 + 0] * matrix[1 * 2 + 1] - matrix[0 * 2 + 1] * matrix[1 * 2 + 0];
    if (fabsf(det) > DET_EPSILON) {
        float inv_det = 1.0f / det;

        inverse[0 * 2 + 0] = + inv_det * matrix[1 * 2 + 1];
        inverse[0 * 2 + 1] = - inv_det * matrix[0 * 2 + 1];
        inverse[1 * 2 + 0] = - inv_det * matrix[1 * 2 + 0];
        inverse[1 * 2 + 1] = + inv_det * matrix[0 * 2 + 0];
    }
    else
        return false;

    return true;
}

template <>
bool Math::inverseMatrix<double, Rt::u1, 2>(MatrixLayout layout, const double matrix[], double inverse[])
{
    double det = matrix[0 * 2 + 0] * matrix[1 * 2 + 1] - matrix[0 * 2 + 1] * matrix[1 * 2 + 0];
    if (fabs(det) > DET_EPSILON) {
        double inv_det = 1.0 / det;

        inverse[0 * 2 + 0] = + inv_det * matrix[1 * 2 + 1];
        inverse[0 * 2 + 1] = - inv_det * matrix[0 * 2 + 1];
        inverse[1 * 2 + 0] = - inv_det * matrix[1 * 2 + 0];
        inverse[1 * 2 + 1] = + inv_det * matrix[0 * 2 + 0];
    }
    else
        return false;

    return true;
}
