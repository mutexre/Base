template <typename T>
Rotation<T>::Rotation() {
    this->initSquareMatrix(4);
    this->data.resize(4 * 4);
    this->loadIdentity();
}

template <typename T>
Rotation<T>::Rotation(T x, T y, T z, T angle, bool normalize) {
    if (normalize) {
        auto len = sqrtf(x * x + y * y + z * z);
        x /= len;
        y /= len;
        z /= len;
    }
    this->initSquareMatrix(4);
    this->data.resize(4 * 4);
    calcRotationMatrix(x, y, z, angle);
}

template <typename T>
T Rotation<T>::f0(T x, T c, T one_minus_c) {
    return c + x * x * one_minus_c;
}

template <typename T>
T Rotation<T>::f1(T x, T y, T z, T c, T s) {
    return x * y * (1.0 - c) - z * s;
}

template <typename T>
void Rotation<T>::calcRotationMatrix(T x, T y, T z, T angle) {
    T s, c, one_minus_c;

    s = sinf(angle);
    c = cosf(angle);
    one_minus_c = T(1) - c;

    this->set(0, 0, f0(x, c, one_minus_c));
    this->set(0, 1, f1(x, y, z, c, s));
    this->set(0, 2, f1(x, z, -y, c, s));
    this->set(0, 3, T(0));

    this->set(1, 0, f1(y, x, -z, c, s));
    this->set(1, 1, f0(y, c, one_minus_c));
    this->set(1, 2, f1(y, z, x, c, s));
    this->set(1, 3, T(0));

    this->set(2, 0, f1(z, x, y, c, s));
    this->set(2, 1, f1(z, y, -x, c, s));
    this->set(2, 2, f0(z, c, one_minus_c));
    this->set(2, 3, T(0));

    this->set(3, 0, T(0));
    this->set(3, 1, T(0));
    this->set(3, 2, T(0));
    this->set(3, 3, T(1));
}
