#ifndef header_80A3AB1C0A61
#define header_80A3AB1C0A61

#include <string.h>

namespace Math
{
    template <typename T = float>
    class SquareMatrix2 : public SquareMatrix<T, Rt::u1, 2>
    {
    public:
        SquareMatrix2() : SquareMatrix<T, Rt::u1, 2>(MatrixLayout::RowMajor) {}
        SquareMatrix2(MatrixLayout layout) : SquareMatrix<T, Rt::u1, 2>(layout) {}
    };
}

#endif
