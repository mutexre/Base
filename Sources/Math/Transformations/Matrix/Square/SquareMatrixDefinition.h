/*
template <typename T, typename I, I N>
void transposeSquareMatrixInPlace(T matrix[])
{
    auto a = matrix;
    for (I row = 0; row < N; row++)
    {
        for (I column = row + 1; column < N; column++)
        {
            auto current_a = a + column;
            auto tmp = *current_a;
            auto b = matrix + column * N + row;

            *current_a = *b;
            *b = tmp;
        }

        a += N;
    }
}
*/

template <typename T, typename I, I N>
void transposeSquareMatrix(const T matrix[], T transpose[])
{
    for (I row = 0; row < N; row++) {
        for (I column = 0; column < N; column++)
            transpose[column * N + row] = matrix[row * N + column];
    }
}
/*
template <typename T, typename I, I N>
bool inverseMatrix(MatrixLayout layout, const T matrix[], T inverse[]) {
    // Cramer's rule or Gaussian elimination (N > 6)
    return false;
}
*/
template <typename T, typename I, I N>
SquareMatrix<T, I, N>::SquareMatrix()
    : Matrix<T, I, N, N>(MatrixLayout::RowMajor)
{}

template <typename T, typename I, I N>
SquareMatrix<T, I, N>::SquareMatrix(MatrixLayout layout)
    : Matrix<T, I, N, N>(layout)
{}
/*
template <typename T, typename I, I N>
void SquareMatrix<T, I, N>::loadIdentity()
{
    for (I i = 0; i < N; i++) {
        for (I j = 0; j < N; j++)
            this->matrix[i * N + j] = (i != j ? T(0) : T(1));
    }
}
*/
template <typename T, typename I, I size>
template <I subMatrixSize>
SquareMatrix<T, I, size>
SquareMatrix<T, I, size>::getSubMatrix(I rowOffset, I columnOffset) const
{
    SquareMatrix<T, I, subMatrixSize> retval(this->layout);
    copyRange(*this, { rowOffset, columnOffset }, retval, { 0, 0 }, { subMatrixSize, subMatrixSize });
    return retval;
}

template <typename T, typename I, I N>
SquareMatrix<T, I, N>&
SquareMatrix<T, I, N>::transpose() {
    transposeSquareMatrixInPlace<T, I, N>(this->matrix);
    return *this;
}

template <typename T, typename I, I N>
SquareMatrix<T, I, N>&
SquareMatrix<T, I, N>::inverse() {
    //std::alignas(16)
#if defined _MSC_VER
    __declspec(align(16))
#endif
    T inverseMatrix[N * N]
#if defined __GNUC__ || defined __clang__
    __attribute__((aligned(16)))
#endif
    ;

    Math::inverseMatrix<T, I, N>(this->layout, this->matrix, inverseMatrix);
    memcpy(this->matrix, inverseMatrix, sizeof(inverseMatrix));
    return *this;
}

template <typename T, typename I, I N>
Rt::Option<SquareMatrix<T, I, N>>
SquareMatrix<T, I, N>::getInversed() const {
    SquareMatrix<T, I, N> inverseTransform;

    if (!inverseMatrix<T, I, N>(this->layout, this->matrix, inverseTransform.matrix))
        return Rt::Option<SquareMatrix<T, I, N>>();

    return Rt::Option<SquareMatrix<T, I, N>>(inverseTransform);
}

template <typename T, typename I, I N>
SquareMatrix<T, I, N>
SquareMatrix<T, I, N>::getTransposed() const {
    SquareMatrix<T, I, N> retval;
    transposeSquareMatrix<T, I, N>(this->matrix, retval.matrix);
    return retval;
}
