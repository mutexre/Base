template <typename T>
Scale<T>::Scale() : x(1.0), y(1.0), z(1.0) {
    this->initSquareMatrix(4);
    this->data.resize(4 * 4);
    calcMatrix();
}

template <typename T>
Scale<T>::Scale(T x, T y, T z)
{
    this->initSquareMatrix(4);
    this->data.resize(4 * 4);
    setXYZ(x, y, z);
    calcMatrix();
}

template <typename T>
void Scale<T>::getXYZ(T& x, T& y, T& z) const {
    x = this->x;
    y = this->y;
    z = this->z;
}

template <typename T>
void Scale<T>::setXYZ(T x, T y, T z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

template <typename T>
T Scale<T>::getX() const {
    return x;
}

template <typename T>
void Scale<T>::setX(T x) {
    this->x = x;
}

template <typename T>
T Scale<T>::getY() const {
    return y;
}

template <typename T>
void Scale<T>::setY(T y) {
    this->y = y;
}

template <typename T>
T Scale<T>::getZ() const {
    return z;
}

template <typename T>
void Scale<T>::setZ(T z) {
    this->z = z;
}

template <typename T>
void Scale<T>::calcMatrix() {
    this->loadIdentity();
    this->Matrix<T>::set(0, 0, x);
    this->Matrix<T>::set(1, 1, y);
    this->Matrix<T>::set(2, 2, z);
}
