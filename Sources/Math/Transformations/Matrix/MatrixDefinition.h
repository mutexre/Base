template <typename T, typename I>
void multiplyRowMajorMatrices(I M, I N, I K, const T* a, const T* b, T* c)
{
#if 0
    auto a_current_element = a;
    auto b_current_column = b;
    auto c_current_element = c;

    while (a_current_element < a + M * N)
    {
        while (b_current_column < b + N)
        {
            *c_current_element = 0.0;

            for (I column = 0; column < N; column++)
            {
                *(c_current_element) += (*a_current_element) * b_current_column[column * N];
                a_current_element++;
            }

            c_current_element++;
            b_current_column++;
        }
    }
#else
    for (I row = 0; row < M; row++)
    {
        for (I column = 0; column < N; column++)
        {
            T val = T(0);
            for (I i = 0; i < N; i++) val += element(a, row, i, N) * element(b, i, column, K);
            element(c, row, column, N) = val;
        }
    }
#endif
}

template <typename T, typename I>
void multiplyColumnMajorMatrices(I M, I N, I K, const T* a, const T* b, T* c)
{
    auto a_current_row = a;
    auto c_current_row = c;

    while (a_current_row < a + M)
    {
        auto b_current_element = b;

        while (b_current_element < b + M * N)
        {
            *c_current_row = 0.0;

            for (unsigned char row = 0; row < M; row++)
            {
                c_current_row[row * M] += a_current_row[row * M] * (*b_current_element);
                b_current_element++;
            }
        }

        a_current_row++;
        c_current_row++;
    }
}

template <typename T, typename I>
void multiplyMatrices(MatrixLayout layout,
                      I M, I N, I K,
                      const T* a, const T* b, T* c)
{
    if (layout == MatrixLayout::RowMajor)
        multiplyRowMajorMatrices(M, N, K, a, b, c);
    else
        multiplyColumnMajorMatrices(M, N, K, a, b, c);
}

template <typename T, typename I, I srcRowsCount, I srcColumnsCount, I dstRowsCount, I dstColumnsCount>
void copyRange(const Matrix<T, I, srcRowsCount, srcColumnsCount>& src,
               MatrixOffset<I> srcOffset,
               Matrix<T, I, dstRowsCount, dstColumnsCount>& dst,
               MatrixOffset<I> dstOffset,
               MatrixRangeSize<I> rangeSize)
{
    if (srcOffset.rows + rangeSize.rows > srcRowsCount || srcOffset.columns + rangeSize.columns > srcColumnsCount ||
        dstOffset.rows + rangeSize.rows > dstRowsCount || dstOffset.columns + rangeSize.columns > dstColumnsCount)
        Rt::error(0xE9185B1A);

    if (src.getLayout() == dst.getLayout()) {
        if (src.getLayout() == MatrixLayout::RowMajor) {
            for (I row = 0; row < rangeSize.rows; row++)
                memcpy(dst.getMatrix() + dstColumnsCount * (dstOffset.rows + row) + dstOffset.columns,
                       src.getMatrix() + srcColumnsCount * (srcOffset.rows + row) + srcOffset.columns,
                       rangeSize.columns * sizeof(T));
        }
        else {
            for (I column = 0; column < rangeSize.columns; column++)
                memcpy(dst.getMatrix() + dstRowsCount * (dstOffset.columns + column) + dstOffset.rows,
                       src.getMatrix() + srcRowsCount * (srcOffset.columns + column) + srcOffset.rows,
                       rangeSize.rows * sizeof(T));
        }
    }
    else {
        for (I row = 0; row < rangeSize.rows; row++)
            for (I column = 0; column < rangeSize.columns; column++)
                dst.set(row, column, src.get(row, column));
    }
}

template <typename T, typename I, I Nrows, I Ncolumns>
Matrix<T, I, Nrows, Ncolumns>::Matrix() : layout(MatrixLayout::RowMajor)
{}

template <typename T, typename I, I Nrows, I Ncolumns>
Matrix<T, I, Nrows, Ncolumns>::Matrix(MatrixLayout layout) {
    this->layout = layout;
}

template <typename T, typename I, I Nrows, I Ncolumns>
Matrix<T, I, Nrows, Ncolumns>&
Matrix<T, I, Nrows, Ncolumns>::
operator=(const Matrix<T, I, Nrows, Ncolumns>& t)
{
    memcpy(matrix, t.matrix, sizeof(matrix));
    return *this;
}

template <typename T, typename I, I Nrows, I Ncolumns>
template <I Nrows2, I Ncolumns2>
Matrix<T, I, Nrows, Ncolumns>&
Matrix<T, I, Nrows, Ncolumns>::operator=(const Matrix<T, I, Nrows2, Ncolumns2>&)
{
    return *this;
}
/*
template <typename T, typename I, I Nrows, I Ncolumns>
template <I Nrows2, I Ncolumns2>
Matrix<T, I, Nrows2, Ncolumns2>
Matrix<T, I, Nrows, Ncolumns>::getSubMatrix() const
{
    Matrix<T, I, Nrows2, Ncolumns2> retval;
    return retval;
}
*/
template <typename T, typename I, I Nrows, I Ncolumns>
Matrix<T, I, Nrows, Nrows>&
Matrix<T, I, Nrows, Ncolumns>::
operator*=(const Matrix<T, I, Ncolumns, Nrows>& t)
{
    T tmp[Nrows * Nrows];

    multiplyMatrices(layout, Nrows, Nrows, Ncolumns, t.matrix, matrix, tmp);
    memcpy(matrix, tmp, sizeof(matrix));

    return *this;
}

template <typename T, typename I, I Nrows, I Ncolumns>
const Matrix<T, I, Nrows, Nrows>
Matrix<T, I, Nrows, Ncolumns>::
operator*(const Matrix<T, I, Ncolumns, Nrows>& t)
{
    Matrix<T, I, Nrows, Nrows> retval;
    multiplyMatrices(layout, Nrows, Nrows, Ncolumns, Nrows, Ncolumns, matrix, t.matrix, retval);
    return retval;
}

template <typename T, typename I, I Nrows, I Ncolumns>
void Matrix<T, I, Nrows, Ncolumns>::multiply(const Matrix<T, I, Ncolumns, Nrows>& t,
                                                                 Matrix<T, I, Nrows, Nrows>& output)
{
    multiplyMatrices(layout, Nrows, Nrows, Ncolumns, matrix, t.matrix, output.matrix);
}

template <typename T, typename I, I Nrows, I Ncolumns>
MatrixLayout Matrix<T, I, Nrows, Ncolumns>::getLayout() const
{
    return layout;
}

template <typename T, typename I, I Nrows, I Ncolumns>
void Matrix<T, I, Nrows, Ncolumns>::setLayout(MatrixLayout layout)
{
//rearrange data in matrix
    this->layout = layout;
}

template <typename T, typename I, I Nrows, I Ncolumns>
unsigned short Matrix<T, I, Nrows, Ncolumns>::getElementOffsetInMatrix(I row, I column) const
{
    return (layout == MatrixLayout::RowMajor ? row * Ncolumns + column : column * Nrows + row);
}

template <typename T, typename I, I Nrows, I Ncolumns>
T Matrix<T, I, Nrows, Ncolumns>::get(I row, I column) const
{
    return matrix[getElementOffsetInMatrix(row, column)];
}

template <typename T, typename I, I Nrows, I Ncolumns>
void Matrix<T, I, Nrows, Ncolumns>::set(I row, I column, T value)
{
    matrix[getElementOffsetInMatrix(row, column)] = value;
}

template <typename T, typename I, I Nrows, I Ncolumns>
T* Matrix<T, I, Nrows, Ncolumns>::getMatrix() const
{
    return (T*)matrix;
}

template <typename T, typename I, I Nrows, I Ncolumns>
void Matrix<T, I, Nrows, Ncolumns>::rowMajorPrint(const T* matrix) const
{
    const T* element = matrix;
    for (I row = 0; row < Nrows; row++)
    {
        for (I column = 0; column < Ncolumns; column++)
            printf("%f ", *(element++));
        printf("\n");
    }
}

template <typename T, typename I, I Nrows, I Ncolumns>
void Matrix<T, I, Nrows, Ncolumns>::columnMajorPrint(const T* matrix) const
{
    for (I row = 0; row < Nrows; row++)
    {
        for (I column = 0; column < Ncolumns; column++)
            printf("%f ", matrix[row * Ncolumns + column]);
        printf("\n");
    }
}

template <typename T, typename I, I Nrows, I Ncolumns>
void Matrix<T, I, Nrows, Ncolumns>::print(const T* matrix) const
{
    if (layout == MatrixLayout::RowMajor)
        rowMajorPrint(matrix);
    else
        columnMajorPrint(matrix);
    printf("\n");
}

template <typename T, typename I, I Nrows, I Ncolumns>
void Matrix<T, I, Nrows, Ncolumns>::printMatrix() const
{
    print(matrix);
}

template <typename T, typename I, I Nrows, I Ncolumns>
void Matrix<T, I, Nrows, Ncolumns>::rowMajorTransform(const T input[Ncolumns], T output[Nrows])
{
    auto matrixElement = matrix;

    for (auto outputElement = output;
         outputElement < output + Nrows;
         outputElement++)
    {
        *outputElement = 0.0;

        for (auto inputElement = input;
             inputElement < input + Ncolumns;
             inputElement++)
        {
            *outputElement += (*matrixElement) * (*inputElement);
            matrixElement++;
        }
    }
}

template <typename T, typename I, I Nrows, I Ncolumns>
void Matrix<T, I, Nrows, Ncolumns>::columnMajorTransform(const T input[Ncolumns], T output[Nrows])
{
    for (I row = 0; row < Nrows; row++)
    {
        output[row] = 0.0;
        for (I column = 0; column < Ncolumns; column++)
            output[row] += matrix[row * Ncolumns + column] * input[column];
    }
}

template <typename T, typename I, I Nrows, I Ncolumns>
void Matrix<T, I, Nrows, Ncolumns>::transform(const T input[Ncolumns], T output[Nrows])
{
    if (layout == MatrixLayout::RowMajor)
        rowMajorTransform(input, output);
    else
        columnMajorTransform(input, output);
}
