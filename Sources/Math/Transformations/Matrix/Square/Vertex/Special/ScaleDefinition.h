template <typename T>
Scale<T>::Scale() : x(1.0), y(1.0), z(1.0) {
    calcMatrix();
}

template <typename T>
Scale<T>::Scale(T x, T y, T z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    calcMatrix();
}

template <typename T>
void Scale<T>::getXYZ(T& x, T& y, T& z) const
{
    x = this->x;
    y = this->y;
    z = this->z;
}

template <typename T>
void Scale<T>::setXYZ(T x, T y, T z)
{
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
T Scale<T>::getZ() const
{
    return z;
}

template <typename T>
void Scale<T>::setZ(T z) {
    this->z = z;
}

template <typename T>
void Scale<T>::calcMatrix()
{
    this->loadIdentity();
    this->matrix[0 * 4 + 0] = x;
    this->matrix[1 * 4 + 1] = y;
    this->matrix[2 * 4 + 2] = z;
}
