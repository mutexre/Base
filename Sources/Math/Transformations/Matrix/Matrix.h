#ifndef header_B6EF17C1E922
#define header_B6EF17C1E922

#include <stdio.h>

#define element(matrix, row, column, N) (matrix)[(row) * (N) + (column)]
#define element2(matrix, row_x_N, column) (matrix)[(row_x_N) + (column)]

namespace Math
{
    enum class MatrixLayout {
        RowMajor,
        ColumnMajor
    };

    template <typename I>
    struct MatrixOffset {
        I rows, columns;

        MatrixOffset(I rows, I columns) {
            this->rows = rows;
            this->columns = columns;
        }
    };

    template <typename I>
    struct MatrixRangeSize {
        I rows, columns;

        MatrixRangeSize(I rows, I columns) {
            this->rows = rows;
            this->columns = columns;
        }
    };

    template <typename T, typename I>
    void multiplyRowMajorMatrices(I M, I N, I K, const T* a, const T* b, T* c);

    template <typename T, typename I>
    void multiplyColumnMajorMatrices(I M, I N, I K, const T* a, const T* b, T* c);

    template <typename T, typename I>
    void multiplyMatrices(MatrixLayout layout, I M, I N, I K, const T* a, const T* B, T* C);

    template <typename T = float, typename I = Rt::u1, I Nrows = 4, I Ncolumns = Nrows>
    class Matrix : public Transformation<T, Ncolumns, Nrows>
    {
    protected:
//        alignas(16)
#if defined _MSC_VER
        __declspec(align(16))
#endif
        T matrix[Nrows * Ncolumns]
#if defined __GNUC__ || defined __clang__
        __attribute__((aligned(16)))
#endif
        ;

        MatrixLayout layout;

        unsigned short getElementOffsetInMatrix(I row, I column) const;

        void rowMajorPrint(const T* matrix) const;
        void columnMajorPrint(const T* matrix) const;
        void print(const T* matrix) const;

        void rowMajorTransform(const T input[Ncolumns], T output[Nrows]);
        void columnMajorTransform(const T input[Ncolumns], T output[Nrows]);

    public:
        Matrix();
        Matrix(MatrixLayout);

        Matrix<T, I, Nrows, Ncolumns>&
        operator=(const Matrix<T, I, Nrows, Ncolumns>&);

        template <I Nrows2, I Ncolumns2>
        Matrix<T, I, Nrows, Ncolumns>&
        operator=(const Matrix<T, I, Nrows2, Ncolumns2>&);
/*
        template <I Nrows2, I Ncolumns2>
        Matrix<T, I, Nrows2, Ncolumns2>
        getSubMatrix() const;
*/
        Matrix<T, I, Nrows, Nrows>&
        operator*=(const Matrix<T, I, Ncolumns, Nrows>&);

        const Matrix<T, I, Nrows, Nrows>
        operator*(const Matrix<T, I, Ncolumns, Nrows>&);

        void multiply(const Matrix<T, I, Ncolumns, Nrows>&,
                      Matrix<T, I, Nrows, Nrows>&);

        MatrixLayout getLayout() const;
        void setLayout(MatrixLayout layout);

        T get(I row, I column) const;
        void set(I row, I column, T);

        T* getMatrix() const;

        //virtual void transpose();
        //virtual Matrix<T, Ncolumns, Nrows> getTransposed() const;

        void printMatrix() const;

        virtual void transform(const T input[Ncolumns], T output[Nrows]);
    };

    template <typename T, typename I, I srcRowsCount, I srcColumnsCount, I dstRowsCount, I dstColumnsCount>
    void copyRange(const Matrix<T, I, srcRowsCount, srcColumnsCount>& src,
                   MatrixOffset<I> srcOffset,
                   Matrix<T, I, dstRowsCount, dstColumnsCount>& dst,
                   MatrixOffset<I> dstOffset,
                   MatrixRangeSize<I> rangeSize);

    #include <Math/Transformations/Matrix/MatrixDefinition.h>
}

#endif
