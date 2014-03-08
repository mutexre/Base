#ifndef header_e5721182984c
#define header_e5721182984c

#include <string.h>

namespace Math
{
    template <typename T = float>
    class SquareMatrix3 : public SquareMatrix<T, Rt::u1, 3>
    {
    public:
        SquareMatrix3() : SquareMatrix<T, Rt::u1, 3>(MatrixLayout::RowMajor) {}
        SquareMatrix3(MatrixLayout layout) : SquareMatrix<T, Rt::u1, 3>(layout) {}

        SquareMatrix2<T> getSubMatrix2(Rt::u1 rowOffset = 0, Rt::u1 columnOffset = 0) const {
            SquareMatrix3<T> retval(this->layout);
            copyRange<T, Rt::u1, 3, 3, 2, 2>(*this, MatrixOffset<Rt::u1>(rowOffset, columnOffset), retval,
                                             MatrixOffset<Rt::u1>(0, 0),
                                             MatrixRangeSize<Rt::u1>(2, 2));
            return retval;
        }
    };
}

#endif
