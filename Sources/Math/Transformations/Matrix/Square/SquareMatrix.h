#ifndef header_9B47766CEB6A
#define header_9B47766CEB6A

#include <string.h>

#define DET_EPSILON 0.0

namespace Math
{
    template <typename T, typename I, I N>
    void transposeSquareMatrixInPlace(T matrix[]);

    template <typename T, typename I, I N>
    void transposeSquareMatrix(const T matrix[], T transpose[]);

    template <typename T, typename I, I N>
    bool inverseMatrix(MatrixLayout layout, const T matrix[], T inverse[]);

    template <>
    bool inverseMatrix<float, Rt::u1, 3>(MatrixLayout layout, const float matrix[], float inverse[]);

    template <>
    bool inverseMatrix<float, Rt::u1, 4>(MatrixLayout layout, const float matrix[], float inverse[]);

    template <typename T = float, typename I = Rt::u1, I N = 4>
    class SquareMatrix : public Matrix<T, I, N, N>
    {
    public:
        SquareMatrix();
        SquareMatrix(MatrixLayout layout);

        virtual void loadIdentity();

        template <I N2>
        SquareMatrix<T, I, N> getSubMatrix(I row = I(0), I column = I(0)) const;

        virtual SquareMatrix<T, I, N>& transpose();
        virtual SquareMatrix<T, I, N>& inverse();

        virtual Rt::Option<SquareMatrix<T, I, N>> getInversed() const;
        virtual SquareMatrix<T, I, N> getTransposed() const;
    };

    #include <Math/Transformations/Matrix/Square/SquareMatrixDefinition.h>
}

#endif
