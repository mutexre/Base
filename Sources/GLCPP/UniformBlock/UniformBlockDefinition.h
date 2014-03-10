/*
template <typename Description, typename T>
T getScalar(Rt::u1* ptr, Layout<Description>* layout, unsigned int var) {
    return *UNIFORM_PTR2(ptr, layout, var, T);
}

template <typename Description, typename T>
void setScalar(Rt::u1* ptr, Layout<Description>* layout, unsigned int var, T value) {
    *UNIFORM_PTR2(ptr, layout, var, T) = value;
}

template <typename Description, typename T>
void setArray(Rt::u1* ptr, Layout<Description>* layout, unsigned int var, T* values, Rt::u4 offset, Rt::u4 count, Rt::u4 stride)
{
    auto uniformStride = UNIFORM_ARRAY_STRIDE2(layout, var);
    Rt::stridedCopy<T>((Rt::u1*)values, stride, UNIFORM_PTR2(ptr, layout, var, Rt::u1) + offset * uniformStride, uniformStride, count);
}

template <typename Description, typename T>
void setMatrix(Rt::u1* ptr, Layout<Description>* layout,
               unsigned int var,
               T* values,
               bool srcIsRowMajor,
               Rt::u4 nRows, Rt::u4 nColumns,
               Rt::u4 rowStride, Rt::u4 columnStride)
{
    auto arrayStride = UNIFORM_ARRAY_STRIDE2(layout, var);
    auto matrixStride = UNIFORM_MATRIX_STRIDE2(layout, var);
    auto dstIsRowMajor = UNIFORM_IS_ROW_MAJOR2(layout, var);
    
    if (arrayStride == 0) arrayStride = sizeof(T);

    if (srcIsRowMajor) {
        if (dstIsRowMajor)
            for (int row = 0; row < nRows; row++)
                Rt::stridedCopy<T>(((Rt::u1*)values) + rowStride * row, columnStride,
                                   UNIFORM_PTR2(ptr, layout, var, Rt::u1) + row * matrixStride, arrayStride,
                                   nColumns);
        else
            for (int column = 0; column < nColumns; column++)
                Rt::stridedCopy<T>(((Rt::u1*)values) + columnStride * column, rowStride,
                                   UNIFORM_PTR2(ptr, layout, var, Rt::u1) + column * arrayStride, matrixStride,
                                   nRows);
    }
    else {
        if (dstIsRowMajor)
            for (int column = 0; column < nColumns; column++)
                Rt::stridedCopy<T>(((Rt::u1*)values) + columnStride * column, rowStride,
                                   UNIFORM_PTR2(ptr, layout, var, Rt::u1) + column * matrixStride, arrayStride,
                                   nRows);
        else
            for (int row = 0; row < nRows; row++)
                Rt::stridedCopy<T>(((Rt::u1*)values) + rowStride * row, columnStride,
                                   UNIFORM_PTR2(ptr, layout, var, Rt::u1) + row * arrayStride, matrixStride,
                                   nColumns);
    }
}
*/