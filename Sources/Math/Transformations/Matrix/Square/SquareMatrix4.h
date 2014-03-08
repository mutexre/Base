#ifndef header_0800200c9a66
#define header_0800200c9a66

#include <string.h>

namespace Math
{
    template <typename T = float>
    class SquareMatrix4 : public SquareMatrix<T, Rt::u1, 4>
    {
    public:
        SquareMatrix4() : SquareMatrix<T, Rt::u1, 4>(MatrixLayout::RowMajor) {}
        SquareMatrix4(MatrixLayout layout) : SquareMatrix<T, Rt::u1, 4>(layout) {}

        SquareMatrix2<T> getSubMatrix2(Rt::u1 rowOffset = 0, Rt::u1 columnOffset = 0) const {
            SquareMatrix3<T> retval(this->layout);
            copyRange<T, Rt::u1, 4, 4, 2, 2>(*this, MatrixOffset<Rt::u1>(rowOffset, columnOffset), retval,
                                             MatrixOffset<Rt::u1>(0, 0),
                                             MatrixRangeSize<Rt::u1>(2, 2));
            return retval;
        }

        SquareMatrix3<T> getSubMatrix3(Rt::u1 rowOffset = 0, Rt::u1 columnOffset = 0) const {
            SquareMatrix3<T> retval(this->layout);
            copyRange<T, Rt::u1, 4, 4, 3, 3>(*this, MatrixOffset<Rt::u1>(rowOffset, columnOffset), retval,
                                             MatrixOffset<Rt::u1>(0, 0),
                                             MatrixRangeSize<Rt::u1>(3, 3));
            return retval;
        }
    };
}

#endif