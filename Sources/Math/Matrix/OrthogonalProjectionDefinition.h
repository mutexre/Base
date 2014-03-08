template <typename T>
OrthogonalProjection<T>::OrthogonalProjection() {
    this->initSquareMatrix(4);
    this->data.resize(4 * 4);
}

template <typename T>
OrthogonalProjection<T>::OrthogonalProjection(T minX, T maxX, T minY, T maxY, T minZ, T maxZ): OrthogonalProjection() {
    min.x = minX;
    max.x = maxX;
    min.y = minY;
    max.y = maxY;
    min.z = minZ;
    max.z = maxZ;

    size.x = max.x - min.x;
    size.y = max.y - min.y;
    size.z = max.z - min.z;

    middle.x = min.x + size.x / T(2);
    middle.y = min.y + size.y / T(2);
    middle.z = min.z + size.z / T(2);

    calcMatrix();
}

template <typename T>
void OrthogonalProjection<T>::transform(const Vertex<T>& vertex,
                                         const Plane<T>& input,
                                         Plane<T>& output)
{
/*    float beta = T(2) * farZ * nearZ / (farZ - nearZ);

    output.a = input.a * beta;
    output.b = input.b * beta;
    output.c = input.d * f;
    output.d = T(0);*/
}

template <typename T>
void OrthogonalProjection<T>::calcMatrix() {
    this->loadIdentity();
    this->Matrix<T>::set(0, 0, T(2) / size.x);
    this->Matrix<T>::set(0, 3, -middle.x * T(2) / size.x);
    this->Matrix<T>::set(1, 1, T(2) / size.y);
    this->Matrix<T>::set(1, 3, -middle.y * T(2) / size.y);
    this->Matrix<T>::set(2, 2, T(2) / size.z);
    this->Matrix<T>::set(2, 3, -middle.z * T(2) / size.z);
    this->Matrix<T>::set(3, 3, T(1));
}
