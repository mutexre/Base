#include <xmmintrin.h>
#include <Math/Math.h>

template <>
void Math::SquareMatrix<float, Rt::u1, 4>::loadIdentity()
{
    static const float identity[4][4] =
    {
        { 1.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 1.0f }
    };
    memcpy(this->matrix, identity, sizeof(identity));
}

template <>
void Math::SquareMatrix<double, Rt::u1, 4>::loadIdentity()
{
    static const double identity[4][4] =
    {
        { 1.0, 0.0, 0.0, 0.0 },
        { 0.0, 1.0, 0.0, 0.0 },
        { 0.0, 0.0, 1.0, 0.0 },
        { 0.0, 0.0, 0.0, 1.0 }
    };
    memcpy(this->matrix, identity, sizeof(identity));
}

template <>
void Math::transposeSquareMatrixInPlace<float, Rt::u1, 4>(float matrix[4 * 4])
{
    __m128 row0, row1, row2, row3;

    row0 = _mm_load_ps(matrix);
    row1 = _mm_load_ps(matrix + 4);
    row2 = _mm_load_ps(matrix + 8);
    row3 = _mm_load_ps(matrix + 12);

    _MM_TRANSPOSE4_PS(row0, row1, row2, row3);

    _mm_store_ps(matrix, row0);
    _mm_store_ps(matrix + 4, row1);
    _mm_store_ps(matrix + 8, row2);
    _mm_store_ps(matrix + 12, row3);
}

template <>
void Math::transposeSquareMatrix<float, Rt::u1, 4>(const float matrix[4 * 4], float transpose[4 * 4])
{
    __m128 row0, row1, row2, row3;

    row0 = _mm_load_ps(matrix);
    row1 = _mm_load_ps(matrix + 4);
    row2 = _mm_load_ps(matrix + 8);
    row3 = _mm_load_ps(matrix + 12);

    _MM_TRANSPOSE4_PS(row0, row1, row2, row3);

    _mm_store_ps(transpose, row0);
    _mm_store_ps(transpose + 4, row1);
    _mm_store_ps(transpose + 8, row2);
    _mm_store_ps(transpose + 12, row3);
}

template <>
void Math::transposeSquareMatrixInPlace<double, Rt::u1, 4>(double matrix[4 * 4])
{
    double tmp;

    tmp = element(matrix, 0, 1, 4);
    element(matrix, 0, 1, 4) = element(matrix, 1, 0, 4);
    element(matrix, 1, 0, 4) = tmp;

    tmp = element(matrix, 0, 2, 4);
    element(matrix, 0, 2, 4) = element(matrix, 2, 0, 4);
    element(matrix, 2, 0, 4) = tmp;

    tmp = element(matrix, 0, 3, 4);
    element(matrix, 0, 3, 4) = element(matrix, 3, 0, 4);
    element(matrix, 3, 0, 4) = tmp;

    tmp = element(matrix, 1, 2, 4);
    element(matrix, 1, 2, 4) = element(matrix, 2, 1, 4);
    element(matrix, 2, 1, 4) = tmp;

    tmp = element(matrix, 1, 3, 4);
    element(matrix, 1, 3, 4) = element(matrix, 3, 1, 4);
    element(matrix, 3, 1, 4) = tmp;

    tmp = element(matrix, 2, 3, 4);
    element(matrix, 2, 3, 4) = element(matrix, 3, 2, 4);
    element(matrix, 3, 2, 4) = tmp;
}

template <>
void Math::transposeSquareMatrix<double, Rt::u1, 4>(const double matrix[4 * 4], double transpose[4 * 4])
{
    for (Rt::u1 i = 0; i < 4; i++)
    {
        Rt::u1 ix4 = i << 2;

        element(transpose, 0, i, 4) = element2(matrix, ix4, 0);
        element(transpose, 1, i, 4) = element2(matrix, ix4, 1);
        element(transpose, 2, i, 4) = element2(matrix, ix4, 2);
        element(transpose, 3, i, 4) = element2(matrix, ix4, 3);
    }
}

template <>
bool Math::inverseMatrix<float, Rt::u1, 4>(MatrixLayout layout, const float matrix[], float inverse[])
{
    /*__m128 row0 = _mm_setr_ps (0.f, 0.f, 0.f, 10.0f), row1, row2, row3;
    __m128 minor0, minor1, minor2, minor3;
    __m128 tmp = _mm_setr_ps (0.f, 0.f, 0.f, 10.0f, det;
    */

    #pragma warning(push)
    #pragma warning( disable : 4700 )

    __m128 tmp = _mm_setr_ps(0.0f, 0.0f, 0.0f, 0.0f);
    tmp = _mm_loadh_pi(_mm_loadl_pi(tmp, (__m64*)matrix), (__m64*)(matrix + 4));

    __m128 row1 = _mm_setr_ps(0.0f, 0.0f, 0.0f, 0.0f);
    row1 = _mm_loadh_pi(_mm_loadl_pi(row1, (__m64*)(matrix + 8)), (__m64*)(matrix + 12));
    
    __m128 row0 = _mm_setr_ps(0.0f, 0.0f, 0.0f, 0.0f);
    row0 = _mm_shuffle_ps(tmp, row1, 0x88);
    row1 = _mm_shuffle_ps(row1, tmp, 0xDD);
    tmp = _mm_loadh_pi(_mm_loadl_pi(tmp, (__m64*)(matrix + 2)), (__m64*)(matrix + 6));
    
    __m128 row3 = _mm_setr_ps(0.0f, 0.0f, 0.0f, 0.0f);
    row3 = _mm_loadh_pi(_mm_loadl_pi(row3, (__m64*)(matrix + 10)), (__m64*)(matrix + 14));
    
    __m128 row2 = _mm_setr_ps(0.0f, 0.0f, 0.0f, 0.0f);
    row2 = _mm_shuffle_ps(tmp, row3, 0x88);
    row3 = _mm_shuffle_ps(row3, tmp, 0xDD);
    #pragma warning(pop)

    tmp = _mm_mul_ps(row2, row3);
    tmp = _mm_shuffle_ps(tmp, tmp, 0xb1);
    
    __m128 minor0 = _mm_setr_ps(0.0f, 0.0f, 0.0f, 0.0f);
    minor0 = _mm_mul_ps(row1, tmp);
    
    __m128 minor1 = _mm_setr_ps(0.0f, 0.0f, 0.0f, 0.0f);
    minor1 = _mm_mul_ps(row0, tmp);
    tmp = _mm_shuffle_ps(tmp, tmp, 0x4e);
    minor0 = _mm_sub_ps(_mm_mul_ps(row1, tmp), minor0);
    minor1 = _mm_sub_ps(_mm_mul_ps(row0, tmp), minor1);
    minor1 = _mm_shuffle_ps(minor1, minor1, 0x4e);

    tmp = _mm_mul_ps(row1, row2);
    tmp = _mm_shuffle_ps(tmp, tmp, 0xB1);
    minor0 = _mm_add_ps(_mm_mul_ps(row3, tmp), minor0);
    
    __m128 minor3 = _mm_setr_ps(0.0f, 0.0f, 0.0f, 0.0f);
    minor3 = _mm_mul_ps(row0, tmp);
    tmp = _mm_shuffle_ps(tmp, tmp, 0x4E);
    minor0 = _mm_sub_ps(minor0, _mm_mul_ps(row3, tmp));
    minor3 = _mm_sub_ps(_mm_mul_ps(row0, tmp), minor3);
    minor3 = _mm_shuffle_ps(minor3, minor3, 0x4E);

    tmp = _mm_mul_ps(_mm_shuffle_ps(row1, row1, 0x4E), row3);
    tmp = _mm_shuffle_ps(tmp, tmp, 0xB1);
    row2 = _mm_shuffle_ps(row2, row2, 0x4E);
    minor0 = _mm_add_ps(_mm_mul_ps(row2, tmp), minor0);
    
    __m128 minor2 = _mm_setr_ps(0.0f, 0.0f, 0.0f, 0.0f);
    minor2 = _mm_mul_ps(row0, tmp);
    tmp = _mm_shuffle_ps(tmp, tmp, 0x4E);
    minor0 = _mm_sub_ps(minor0, _mm_mul_ps(row2, tmp));
    minor2 = _mm_sub_ps(_mm_mul_ps(row0, tmp), minor2);
    minor2 = _mm_shuffle_ps(minor2, minor2, 0x4E);

    tmp = _mm_mul_ps(row0, row1);
    tmp = _mm_shuffle_ps(tmp, tmp, 0xB1);
    minor2 = _mm_add_ps(_mm_mul_ps(row3, tmp), minor2);
    minor3 = _mm_sub_ps(_mm_mul_ps(row2, tmp), minor3);
    tmp = _mm_shuffle_ps(tmp, tmp, 0x4E);
    minor2 = _mm_sub_ps(_mm_mul_ps(row3, tmp), minor2);
    minor3 = _mm_sub_ps(minor3, _mm_mul_ps(row2, tmp));

    tmp = _mm_mul_ps(row0, row3);
    tmp = _mm_shuffle_ps(tmp, tmp, 0xB1);
    minor1 = _mm_sub_ps(minor1, _mm_mul_ps(row2, tmp));
    minor2 = _mm_add_ps(_mm_mul_ps(row1, tmp), minor2);
    tmp = _mm_shuffle_ps(tmp, tmp, 0x4E);
    minor1 = _mm_add_ps(_mm_mul_ps(row2, tmp), minor1);
    minor2 = _mm_sub_ps(minor2, _mm_mul_ps(row1, tmp));

    tmp = _mm_mul_ps(row0, row2);
    tmp = _mm_shuffle_ps(tmp, tmp, 0xB1);
    minor1 = _mm_add_ps(_mm_mul_ps(row3, tmp), minor1);
    minor3 = _mm_sub_ps(minor3, _mm_mul_ps(row1, tmp));
    tmp = _mm_shuffle_ps(tmp, tmp, 0x4E);
    minor1 = _mm_sub_ps(minor1, _mm_mul_ps(row3, tmp));
    minor3 = _mm_add_ps(_mm_mul_ps(row1, tmp), minor3);

    __m128 det = _mm_mul_ps(row0, minor0);
    det = _mm_add_ps(_mm_shuffle_ps(det, det, 0x4E), det);
    det = _mm_add_ss(_mm_shuffle_ps(det, det, 0xB1), det);
    tmp = _mm_rcp_ss(det);

    det = _mm_sub_ss(_mm_add_ss(tmp, tmp), _mm_mul_ss(det, _mm_mul_ss(tmp, tmp)));
    det = _mm_shuffle_ps(det, det, 0x00);

    minor0 = _mm_mul_ps(det, minor0);
    minor1 = _mm_mul_ps(det, minor1);
    minor2 = _mm_mul_ps(det, minor2);
    minor3 = _mm_mul_ps(det, minor3);

    _mm_store_ps(inverse, minor0);
    _mm_store_ps(inverse + 4, minor1);
    _mm_store_ps(inverse + 8, minor2);
    _mm_store_ps(inverse + 12, minor3);

    return true;
}

template <>
bool Math::inverseMatrix<double, Rt::u1, 4>(MatrixLayout layout, const double matrix[4 * 4], double inverse[4 * 4])
{
    return true;
}
