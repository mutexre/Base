template <typename T>
Translation<T>::Translation() : x(T(0)), y(T(0)), z(T(0)) {
    this->initSquareMatrix(4);
    this->data.resize(4 * 4);
    calcMatrix();
}

template <typename T>
Translation<T>::Translation(T x, T y, T z) {
    this->initSquareMatrix(4);
    this->data.resize(4 * 4);
    this->set(x, y, z);
    calcMatrix();
}

template <typename T>
void Translation<T>::get(T& x, T& y, T& z) const {
    x = this->x;
    y = this->y;
    z = this->z;
}

template <typename T>
void Translation<T>::set(T x, T y, T z) {
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
void Translation<T>::calcMatrix() {
    this->loadIdentity();
    this->Matrix<T>::set(0, 3, x);
    this->Matrix<T>::set(1, 3, y);
    this->Matrix<T>::set(2, 3, z);
}
