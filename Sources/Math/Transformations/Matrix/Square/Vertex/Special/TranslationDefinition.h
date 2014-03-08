template <typename T>
Translation<T>::Translation() : x(0.0), y(0.0), z(0.0) {
    calcMatrix();
}

template <typename T>
Translation<T>::Translation(T x, T y, T z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    calcMatrix();
}

template <typename T>
void Translation<T>::get(T& x, T& y, T& z) const
{
    x = this->x;
    y = this->y;
    z = this->z;
}

template <typename T>
void Translation<T>::set(T x, T y, T z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

template <typename T>
T Translation<T>::getX() const {
    return x;
}

template <typename T>
void Translation<T>::setX(T x) {
    this->x = x;
}

template <typename T>
T Translation<T>::getY() const {
    return y;
}

template <typename T>
void Translation<T>::setY(T y) {
    this->y = y;
}

template <typename T>
T Translation<T>::getZ() const {
    return z;
}

template <typename T>
void Translation<T>::setZ(T z) {
    this->z = z;
}

template <typename T>
void Translation<T>::calcMatrix()
{
    this->loadIdentity();

    if (this->layout == MatrixLayout::RowMajor)
    {
        this->matrix[0 * 4 + 3] = x;
        this->matrix[1 * 4 + 3] = y;
        this->matrix[2 * 4 + 3] = z;
    }
    else
    {
        this->matrix[12 + 0] = x;
        this->matrix[12 + 1] = y;
        this->matrix[12 + 2] = z;
    }
}
