#include <math.h>
#include <Math/Math.h>

template <>
void Math::SquareMatrix<float, Rt::u1, 3>::loadIdentity()
{
    static const float identity[3][3] =
    {
        { 1.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f }
    };
    memcpy(this->matrix, identity, sizeof(identity));
}

template <>
void Math::SquareMatrix<double, Rt::u1, 3>::loadIdentity()
{
    static const double identity[3][3] =
    {
        { 1.0, 0.0, 0.0 },
        { 0.0, 1.0, 0.0 },
        { 0.0, 0.0, 1.0 }
    };
    memcpy(this->matrix, identity, sizeof(identity));
}

template <>
void Math::transposeSquareMatrixInPlace<float, Rt::u1, 3>(float matrix[9])
{
    float tmp;

    tmp = element(matrix, 0, 1, 3);
    element(matrix, 0, 1, 3) = element(matrix, 1, 0, 3);
    element(matrix, 1, 0, 3) = tmp;

    tmp = element(matrix, 0, 2, 3);
    element(matrix, 0, 2, 3) = element(matrix, 2, 0, 3);
    element(matrix, 2, 0, 3) = tmp;

    tmp = element(matrix, 1, 2, 3);
    element(matrix, 1, 2, 3) = element(matrix, 2, 1, 3);
    element(matrix, 2, 1, 3) = tmp;
}

template <>
void Math::transposeSquareMatrix<float, Rt::u1, 3>(const float matrix[3 * 3], float transpose[3 * 3])
{
    element(transpose, 0, 0, 3) = element(matrix, 0, 0, 3);
    element(transpose, 0, 1, 3) = element(matrix, 1, 0, 3);
    element(transpose, 0, 2, 3) = element(matrix, 2, 0, 3);

    element(transpose, 1, 0, 3) = element(matrix, 0, 1, 3);
    element(transpose, 1, 1, 3) = element(matrix, 1, 1, 3);
    element(transpose, 1, 2, 3) = element(matrix, 2, 1, 3);

    element(transpose, 2, 0, 3) = element(matrix, 0, 2, 3);
    element(transpose, 2, 1, 3) = element(matrix, 1, 2, 3);
    element(transpose, 2, 2, 3) = element(matrix, 2, 2, 3);
}

template <>
void Math::transposeSquareMatrixInPlace<double, Rt::u1, 3>(double matrix[3 * 3])
{
    double tmp;

    tmp = element(matrix, 0, 1, 3);
    element(matrix, 0, 1, 3) = element(matrix, 1, 0, 3);
    element(matrix, 1, 0, 3) = tmp;

    tmp = element(matrix, 0, 2, 3);
    element(matrix, 0, 2, 3) = element(matrix, 2, 0, 3);
    element(matrix, 2, 0, 3) = tmp;

    tmp = element(matrix, 1, 2, 3);
    element(matrix, 1, 2, 3) = element(matrix, 2, 1, 3);
    element(matrix, 2, 1, 3) = tmp;
}

template <>
void Math::transposeSquareMatrix<double, Rt::u1, 3>(const double matrix[3 * 3], double transpose[3 * 3])
{
    element(transpose, 0, 0, 3) = element(matrix, 0, 0, 3);
    element(transpose, 0, 1, 3) = element(matrix, 1, 0, 3);
    element(transpose, 0, 2, 3) = element(matrix, 2, 0, 3);

    element(transpose, 1, 0, 3) = element(matrix, 0, 1, 3);
    element(transpose, 1, 1, 3) = element(matrix, 1, 1, 3);
    element(transpose, 1, 2, 3) = element(matrix, 2, 1, 3);

    element(transpose, 2, 0, 3) = element(matrix, 0, 2, 3);
    element(transpose, 2, 1, 3) = element(matrix, 1, 2, 3);
    element(transpose, 2, 2, 3) = element(matrix, 2, 2, 3);
}

template <>
bool Math::inverseMatrix<float, Rt::u1, 3>(MatrixLayout layout, const float matrix[3 * 3], float inverse[3 * 3])
{
    float det = element(matrix, 0, 0, 3) * (element(matrix, 2, 2, 3) * element(matrix, 1, 1, 3) - element(matrix, 2, 1, 3) * element(matrix, 1, 2, 3)) +
                element(matrix, 0, 1, 3) * (element(matrix, 1, 2, 3) * element(matrix, 2, 0, 3) - element(matrix, 1, 0, 3) * element(matrix, 2, 2, 3)) +
                element(matrix, 0, 2, 3) * (element(matrix, 1, 0, 3) * element(matrix, 2, 1, 3) - element(matrix, 1, 1, 3) * element(matrix, 2, 0, 3));

    if (fabsf(det) > DET_EPSILON)
    {
        float inv_det = 1.0f / det;

        element(inverse, 0, 0, 3) = + inv_det * (element(matrix, 2, 2, 3) * element(matrix, 1, 1, 3) - element(matrix, 2, 1, 3) * element(matrix, 1, 2, 3));
        element(inverse, 0, 1, 3) = - inv_det * (element(matrix, 2, 2, 3) * element(matrix, 0, 1, 3) - matrix[2 * 3 + 1] * matrix[0 * 3 + 2]);
        element(inverse, 0, 2, 3) = + inv_det * (matrix[1 * 3 + 2] * matrix[0 * 3 + 1] - matrix[1 * 3 + 1] * matrix[0 * 3 + 2]);

        element(inverse, 1, 0, 3) = - inv_det * (matrix[2 * 3 + 2] * matrix[1 * 3 + 0] - matrix[2 * 3 + 0] * matrix[1 * 3 + 2]);
        element(inverse, 1, 1, 3) = + inv_det * (matrix[2 * 3 + 2] * matrix[0 * 3 + 0] - matrix[2 * 3 + 0] * matrix[0 * 3 + 2]);
        element(inverse, 1, 2, 3) = - inv_det * (matrix[1 * 3 + 2] * matrix[0 * 3 + 0] - matrix[1 * 3 + 0] * matrix[0 * 3 + 2]);

        element(inverse, 2, 0, 3) = + inv_det * (matrix[2 * 3 + 1] * matrix[1 * 3 + 0] - matrix[2 * 3 + 0] * matrix[1 * 3 + 1]);
        element(inverse, 2, 1, 3) = - inv_det * (matrix[2 * 3 + 1] * matrix[0 * 3 + 0] - matrix[2 * 3 + 0] * matrix[0 * 3 + 1]);
        element(inverse, 2, 2, 3) = + inv_det * (matrix[1 * 3 + 1] * matrix[0 * 3 + 0] - matrix[1 * 3 + 0] * matrix[0 * 3 + 1]);
    }
    else
    {
        return false;
    }

    return true;
}

template <>
bool Math::inverseMatrix<double, Rt::u1, 3>(MatrixLayout layout, const double matrix[3 * 3], double inverse[3 * 3])
{
    double det = element(matrix, 0, 0, 3) * (element(matrix, 2, 2, 3) * element(matrix, 1, 1, 3) - element(matrix, 2, 1, 3) * element(matrix, 1, 2, 3)) +
                 element(matrix, 0, 1, 3) * (element(matrix, 1, 2, 3) * element(matrix, 2, 0, 3) - element(matrix, 1, 0, 3) * element(matrix, 2, 2, 3)) +
                 element(matrix, 0, 2, 3) * (element(matrix, 1, 0, 3) * element(matrix, 2, 1, 3) - element(matrix, 1, 1, 3) * element(matrix, 2, 0, 3));

    if (fabs(det) > DET_EPSILON)
    {
        double inv_det = 1.0 / det;

        inverse[0 * 3 + 0] = + inv_det * (matrix[2 * 3 + 2] * matrix[1 * 3 + 1] - matrix[2 * 3 + 1] * matrix[1 * 3 + 2]);
        inverse[0 * 3 + 1] = - inv_det * (matrix[2 * 3 + 2] * matrix[0 * 3 + 1] - matrix[2 * 3 + 1] * matrix[0 * 3 + 2]);
        inverse[0 * 3 + 2] = + inv_det * (matrix[1 * 3 + 2] * matrix[0 * 3 + 1] - matrix[1 * 3 + 1] * matrix[0 * 3 + 2]);

        inverse[1 * 3 + 0] = - inv_det * (matrix[2 * 3 + 2] * matrix[1 * 3 + 0] - matrix[2 * 3 + 0] * matrix[1 * 3 + 2]);
        inverse[1 * 3 + 1] = + inv_det * (matrix[2 * 3 + 2] * matrix[0 * 3 + 0] - matrix[2 * 3 + 0] * matrix[0 * 3 + 2]);
        inverse[1 * 3 + 2] = - inv_det * (matrix[1 * 3 + 2] * matrix[0 * 3 + 0] - matrix[1 * 3 + 0] * matrix[0 * 3 + 2]);

        inverse[2 * 3 + 0] = + inv_det * (matrix[2 * 3 + 1] * matrix[1 * 3 + 0] - matrix[2 * 3 + 0] * matrix[1 * 3 + 1]);
        inverse[2 * 3 + 1] = - inv_det * (matrix[2 * 3 + 1] * matrix[0 * 3 + 0] - matrix[2 * 3 + 0] * matrix[0 * 3 + 1]);
        inverse[2 * 3 + 2] = + inv_det * (matrix[1 * 3 + 1] * matrix[0 * 3 + 0] - matrix[1 * 3 + 0] * matrix[0 * 3 + 1]);
    }
    else
        return false;

    return true;
}
