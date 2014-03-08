template <typename T>
T Rotation<T>::f0(T x, T c, T one_minus_c)
{
    return c + x * x * one_minus_c;
}

template <typename T>
T Rotation<T>::f1(T x, T y, T z, T c, T s)
{
    return x * y * (1.0 - c) - z * s;
}

template <typename T>
void Rotation<T>::calcRotationMatrix(T x, T y, T z, T angle)
{
    T s, c, one_minus_c;

    s = sinf(angle);
    c = cosf(angle);
    one_minus_c = T(1) - c;

    if (this->layout == MatrixLayout::RowMajor)
    {
        element(this->matrix, 0, 0, 4) = f0(x, c, one_minus_c);
        element(this->matrix, 0, 1, 4) = f1(x, y, z, c, s);
        element(this->matrix, 0, 2, 4) = f1(x, z, -y, c, s);
        element(this->matrix, 0, 3, 4) = T(0);

        element(this->matrix, 1, 0, 4) = f1(y, x, -z, c, s);
        element(this->matrix, 1, 1, 4) = f0(y, c, one_minus_c);
        element(this->matrix, 1, 2, 4) = f1(y, z, x, c, s);
        element(this->matrix, 1, 3, 4) = T(0);

        element(this->matrix, 2, 0, 4) = f1(z, x, y, c, s);
        element(this->matrix, 2, 1, 4) = f1(z, y, -x, c, s);
        element(this->matrix, 2, 2, 4) = f0(z, c, one_minus_c);
        element(this->matrix, 2, 3, 4) = T(0);

        element(this->matrix, 3, 0, 4) = T(0);
        element(this->matrix, 3, 1, 4) = T(0);
        element(this->matrix, 3, 2, 4) = T(0);
        element(this->matrix, 3, 3, 4) = T(1);
    }
    else
    {
        element(this->matrix, 0, 0, 4) = f0(x, c, one_minus_c);
        element(this->matrix, 0, 1, 4) = f1(y, x, -z, c, s);
        element(this->matrix, 0, 2, 4) = f1(z, x, y, c, s);
        element(this->matrix, 0, 0, 4) = T(0);

        element(this->matrix, 1, 0, 4) = f1(x, y, z, c, s);
        element(this->matrix, 1, 1, 4) = f0(y, c, one_minus_c);
        element(this->matrix, 1, 2, 4) = f1(z, y, -x, c, s);
        element(this->matrix, 1, 0, 4) = T(0);

        element(this->matrix, 2, 0, 4) = f1(x, z, -y, c, s);
        element(this->matrix, 2, 1, 4) = f1(y, z, x, c, s);
        element(this->matrix, 2, 2, 4) = f0(z, c, one_minus_c);
        element(this->matrix, 2, 3, 4) = T(0);

        element(this->matrix, 3, 0, 4) = T(0);
        element(this->matrix, 3, 1, 4) = T(0);
        element(this->matrix, 3, 2, 4) = T(0);
        element(this->matrix, 3, 3, 4) = T(1);
    }
}

template <typename T>
Rotation<T>::Rotation() {
    this->loadIdentity();
}

template <typename T>
Rotation<T>::Rotation(T x, T y, T z, T angle, bool normalize)
{
    if (normalize) {
        auto len = sqrtf(x * x + y * y + z * z);
        x /= len;
        y /= len;
        z /= len;
    }
    calcRotationMatrix(x, y, z, angle);
}
