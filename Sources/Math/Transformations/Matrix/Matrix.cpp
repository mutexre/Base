#include <immintrin.h>
#include <Math/Math.h>

#if 0
template <>
void Math::Matrix<float, 4, 4>::multiply(const Matrix<float, 4, 4>& t, Matrix<float, 4, 4>& output)
{
    __m128 t_r0, t_r1, t_r2, t_r3;
    __m128 t_c0, t_c1, t_c2, t_c3;
    __m128 r0, r1, r2, r3;
    __m128 tmp;
    __m128 dot0, dot1, dot2, dot3;
    __m128 out_row0, out_row1, out_row2, out_row3;

    tmp = _mm_loadh_pi(_mm_loadl_pi(tmp, (__m64*)(t.matrix + 0)), (__m64*)(t.matrix + 4));
    t_c1 = _mm_loadh_pi(_mm_loadl_pi(t_c1, (__m64*)(t.matrix + 8)), (__m64*)(t.matrix + 12));
    t_c0 = _mm_shuffle_ps(tmp, t_c1, 0x88);
    t_c1 = _mm_shuffle_ps(t_c1, tmp, 0xDD);

    tmp = _mm_loadh_pi(_mm_loadl_pi(tmp, (__m64*)(t.matrix + 2)), (__m64*)(t.matrix + 6));
    t_c3 = _mm_loadh_pi(_mm_loadl_pi(t_c3, (__m64*)(t.matrix + 10)), (__m64*)(t.matrix + 14));
    t_c2 = _mm_shuffle_ps(tmp, t_c3, 0x88);
    t_c3 = _mm_shuffle_ps(t_c3, tmp, 0xDD);

/*
    t_r0 = _mm_load_ps(t.matrix);
    t_r1 = _mm_load_ps(t.matrix + 4);
    t_r2 = _mm_load_ps(t.matrix + 8);
    t_r3 = _mm_load_ps(t.matrix + 12);

    t_c0 = _mm_blend_ps(_mm_blend_ps(t_r0, t_r1, 0x2), _mm_blend_ps(t_r2, t_r3, 0x8), 0xc);
    t_c1 = _mm_blend_ps(_mm_blend_ps(t_r0, t_r1, 0x2), _mm_blend_ps(t_r2, t_r3, 0x8), 0xc);
    t_c2 = _mm_blend_ps(_mm_blend_ps(t_r0, t_r1, 0x2), _mm_blend_ps(t_r2, t_r3, 0x8), 0xc);
    t_c3 = _mm_blend_ps(_mm_blend_ps(t_r0, t_r1, 0x2), _mm_blend_ps(t_r2, t_r3, 0x8), 0xc);
*/

    r0 = _mm_load_ps(matrix);
    r1 = _mm_load_ps(matrix + 4);
    r2 = _mm_load_ps(matrix + 8);
    r3 = _mm_load_ps(matrix + 12);

    dot0 = _mm_dp_ps(r0, t_c0, 0xf1);
    dot1 = _mm_dp_ps(r0, t_c1, 0xf2);
    dot2 = _mm_dp_ps(r0, t_c2, 0xf4);
    dot3 = _mm_dp_ps(r0, t_c3, 0xf8);
    out_row0 = _mm_blend_ps(_mm_blend_ps(dot0, dot1, 0x2), _mm_blend_ps(dot2, dot3, 0x8), 0xc);

    dot0 = _mm_dp_ps(r1, t_c0, 0xf1);
    dot1 = _mm_dp_ps(r1, t_c1, 0xf2);
    dot2 = _mm_dp_ps(r1, t_c2, 0xf4);
    dot3 = _mm_dp_ps(r1, t_c3, 0xf8);
    out_row1 = _mm_blend_ps(_mm_blend_ps(dot0, dot1, 0x2), _mm_blend_ps(dot2, dot3, 0x8), 0xc);

    dot0 = _mm_dp_ps(r2, t_c0, 0xf1);
    dot1 = _mm_dp_ps(r2, t_c1, 0xf2);
    dot2 = _mm_dp_ps(r2, t_c2, 0xf4);
    dot3 = _mm_dp_ps(r2, t_c3, 0xf8);
    out_row2 = _mm_blend_ps(_mm_blend_ps(dot0, dot1, 0x2), _mm_blend_ps(dot2, dot3, 0x8), 0xc);

    dot0 = _mm_dp_ps(r3, t_c0, 0xf1);
    dot1 = _mm_dp_ps(r3, t_c1, 0xf2);
    dot2 = _mm_dp_ps(r3, t_c2, 0xf4);
    dot3 = _mm_dp_ps(r3, t_c3, 0xf8);
    out_row3 = _mm_blend_ps(_mm_blend_ps(dot0, dot1, 0x2), _mm_blend_ps(dot2, dot3, 0x8), 0xc);

    _mm_store_ps(output.matrix, out_row0);
    _mm_store_ps(output.matrix + 4, out_row1);
    _mm_store_ps(output.matrix + 8, out_row2);
    _mm_store_ps(output.matrix + 12, out_row3);

/*
    if (layout == MatrixLayout::RowMajor)
    {
        element(output.matrix, 0, 0, 4) = element(matrix, 0, 0, 4) * element(t.matrix, 0, 0, 4) +
                                          element(matrix, 0, 1, 4) * element(t.matrix, 1, 0, 4) +
                                          element(matrix, 0, 2, 4) * element(t.matrix, 2, 0, 4) +
                                          element(matrix, 0, 3, 4) * element(t.matrix, 3, 0, 4);

        element(output.matrix, 0, 1, 4) = element(matrix, 0, 0, 4) * element(t.matrix, 0, 1, 4) +
                                          element(matrix, 0, 1, 4) * element(t.matrix, 1, 1, 4) +
                                          element(matrix, 0, 2, 4) * element(t.matrix, 2, 1, 4) +
                                          element(matrix, 0, 3, 4) * element(t.matrix, 3, 1, 4);

        element(output.matrix, 0, 2, 4) = element(matrix, 0, 0, 4) * element(t.matrix, 0, 2, 4) +
                                          element(matrix, 0, 1, 4) * element(t.matrix, 1, 2, 4) +
                                          element(matrix, 0, 2, 4) * element(t.matrix, 2, 2, 4) +
                                          element(matrix, 0, 3, 4) * element(t.matrix, 3, 2, 4);

        element(output.matrix, 0, 3, 4) = element(matrix, 0, 0, 4) * element(t.matrix, 0, 3, 4) +
                                          element(matrix, 0, 1, 4) * element(t.matrix, 1, 3, 4) +
                                          element(matrix, 0, 2, 4) * element(t.matrix, 2, 3, 4) +
                                          element(matrix, 0, 3, 4) * element(t.matrix, 3, 3, 4);

        element(output.matrix, 1, 0, 4) = element(matrix, 1, 0, 4) * element(t.matrix, 0, 0, 4) +
                                          element(matrix, 1, 1, 4) * element(t.matrix, 1, 0, 4) +
                                          element(matrix, 1, 2, 4) * element(t.matrix, 2, 0, 4) +
                                          element(matrix, 1, 3, 4) * element(t.matrix, 3, 0, 4);

        element(output.matrix, 1, 1, 4) = element(matrix, 1, 0, 4) * element(t.matrix, 0, 1, 4) +
                                          element(matrix, 1, 1, 4) * element(t.matrix, 1, 1, 4) +
                                          element(matrix, 1, 2, 4) * element(t.matrix, 2, 1, 4) +
                                          element(matrix, 1, 3, 4) * element(t.matrix, 3, 1, 4);

        element(output.matrix, 1, 2, 4) = element(matrix, 1, 0, 4) * element(t.matrix, 0, 2, 4) +
                                          element(matrix, 1, 1, 4) * element(t.matrix, 1, 2, 4) +
                                          element(matrix, 1, 2, 4) * element(t.matrix, 2, 2, 4) +
                                          element(matrix, 1, 3, 4) * element(t.matrix, 3, 2, 4);

        element(output.matrix, 1, 3, 4) = element(matrix, 1, 0, 4) * element(t.matrix, 0, 3, 4) +
                                          element(matrix, 1, 1, 4) * element(t.matrix, 1, 3, 4) +
                                          element(matrix, 1, 2, 4) * element(t.matrix, 2, 3, 4) +
                                          element(matrix, 1, 3, 4) * element(t.matrix, 3, 3, 4);

        element(output.matrix, 2, 0, 4) = element(matrix, 2, 0, 4) * element(t.matrix, 0, 0, 4) +
                                          element(matrix, 2, 1, 4) * element(t.matrix, 1, 0, 4) +
                                          element(matrix, 2, 2, 4) * element(t.matrix, 2, 0, 4) +
                                          element(matrix, 2, 3, 4) * element(t.matrix, 3, 0, 4);

        element(output.matrix, 2, 1, 4) = element(matrix, 2, 0, 4) * element(t.matrix, 0, 1, 4) +
                                          element(matrix, 2, 1, 4) * element(t.matrix, 1, 1, 4) +
                                          element(matrix, 2, 2, 4) * element(t.matrix, 2, 1, 4) +
                                          element(matrix, 2, 3, 4) * element(t.matrix, 3, 1, 4);

        element(output.matrix, 2, 2, 4) = element(matrix, 2, 0, 4) * element(t.matrix, 0, 2, 4) +
                                          element(matrix, 2, 1, 4) * element(t.matrix, 1, 2, 4) +
                                          element(matrix, 2, 2, 4) * element(t.matrix, 2, 2, 4) +
                                          element(matrix, 2, 3, 4) * element(t.matrix, 3, 2, 4);

        element(output.matrix, 2, 3, 4) = element(matrix, 2, 0, 4) * element(t.matrix, 0, 3, 4) +
                                          element(matrix, 2, 1, 4) * element(t.matrix, 1, 3, 4) +
                                          element(matrix, 2, 2, 4) * element(t.matrix, 2, 3, 4) +
                                          element(matrix, 2, 3, 4) * element(t.matrix, 3, 3, 4);

        element(output.matrix, 3, 0, 4) = element(matrix, 3, 0, 4) * element(t.matrix, 0, 0, 4) +
                                          element(matrix, 3, 1, 4) * element(t.matrix, 1, 0, 4) +
                                          element(matrix, 3, 2, 4) * element(t.matrix, 2, 0, 4) +
                                          element(matrix, 3, 3, 4) * element(t.matrix, 3, 0, 4);

        element(output.matrix, 3, 1, 4) = element(matrix, 3, 0, 4) * element(t.matrix, 0, 1, 4) +
                                          element(matrix, 3, 1, 4) * element(t.matrix, 1, 1, 4) +
                                          element(matrix, 3, 2, 4) * element(t.matrix, 2, 1, 4) +
                                          element(matrix, 3, 3, 4) * element(t.matrix, 3, 1, 4);

        element(output.matrix, 3, 2, 4) = element(matrix, 3, 0, 4) * element(t.matrix, 0, 2, 4) +
                                          element(matrix, 3, 1, 4) * element(t.matrix, 1, 2, 4) +
                                          element(matrix, 3, 2, 4) * element(t.matrix, 2, 2, 4) +
                                          element(matrix, 3, 3, 4) * element(t.matrix, 3, 2, 4);

        element(output.matrix, 3, 3, 4) = element(matrix, 3, 0, 4) * element(t.matrix, 0, 3, 4) +
                                          element(matrix, 3, 1, 4) * element(t.matrix, 1, 3, 4) +
                                          element(matrix, 3, 2, 4) * element(t.matrix, 2, 3, 4) +
                                          element(matrix, 3, 3, 4) * element(t.matrix, 3, 3, 4);
    }
*/
}
#endif
