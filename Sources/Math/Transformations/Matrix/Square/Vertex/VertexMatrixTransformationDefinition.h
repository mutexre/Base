template <typename T>
void VertexMatrixTransformation<T>::transform(const Vertex<T>& input, Vertex<T>& output)
{
    SquareMatrix<T, Rt::u1, 4>::transform((const T*)&input, (T*)&output);
}
