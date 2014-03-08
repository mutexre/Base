#include <math.h>
#include <Math/Vertex.h>

template <typename T>
Math::Vector<T>::Vector() {}

template <typename T>
Math::Vector<T>::Vector(T x) : Vector(x, x, x) {}

template <typename T>
Math::Vector<T>::Vector(T x, T y, T z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

template <typename T>
Math::Vector<T>::Vector(const Vector<T>& v) : x(v.x), y(v.y), z(v.z) {}

template <typename T>
Math::Vector<T>::Vector(const Vector<T>* v) : x(v->x), y(v->y), z(v->z) {}

template <typename T>
Math::Vector<T>::Vector(const Vertex<T>& v) : x(v.x / v.w), y(v.y / v.w), z(v.z / v.w) {}

template <typename T>
Math::Vector<T>::Vector(const Vertex<T>* v) : x(v->x / v->w), y(v->y / v->w), z(v->z / v->w) {}

/*
template <typename T>
Vector<T>& Math::Vector<T>::operator-(const Vector<T>& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}
*/

template <typename T>
Math::Vector<T> Math::Vector<T>::operator-(const Vector<T>& v) const {
    return Vector<T>(x - v.x, y - v.y, z - v.z);
}

template <typename T>
Math::Vector<T>& Math::Vector<T>::operator+(const Vector<T>& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

template <typename T>
Math::Vector<T>& Math::Vector<T>::operator*(T value) {
    x *= value;
    y *= value;
    z *= value;
    return *this;
}

template <typename T>
Math::Vector<T>& Math::Vector<T>::operator/(T value) {
    x /= value;
    y /= value;
    z /= value;
    return *this;
}

template <typename T>
Math::Vector<T>& Math::Vector<T>::operator-=(const Vector<T>& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

template <typename T>
Math::Vector<T>& Math::Vector<T>::operator+=(const Vector<T>& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

template <typename T>
Math::Vector<T>& Math::Vector<T>::operator*=(T value) {
    x *= value;
    y *= value;
    z *= value;
    return *this;
}

template <typename T>
Math::Vector<T>& Math::Vector<T>::operator/=(T value) {
    x /= value;
    y /= value;
    z /= value;
    return *this;
}

template <typename T>
T Math::Vector<T>::operator*(const Vector<T>& that) {
    return scalarProduct(that);
}

template <typename T>
Math::Vector<T>& Math::Vector<T>::operator=(T value) {
    x = y = z = value;
    return *this;
}

template <typename T>
T Math::Vector<T>::powOf2OfLength() const {
    return x * x + y * y + z * z;
}

template <typename T>
T Math::Vector<T>::length() const {
    return sqrtf(x * x + y * y + z * z);
}

template <typename T>
T Math::Vector<T>::scalarProduct(const Vector<T>& that) const {
    return x * that.x + y * that.y + z * that.z;
}

template <typename T>
Math::Vector<T>
Math::Vector<T>::crossProduct(const Vector<T>& that) const {
    Vector<T> retval;
    retval.x = y * that.z - z * that.y;
    retval.y = z * that.x - x * that.z;
    retval.z = x * that.y - y * that.x;
    return retval;
}

template <typename T>
Math::Vector<T>& Math::Vector<T>::normalize() {
    return *this / length();
}

template <typename T>
void Math::Vector<T>::print() const {
    printf("%f %f %f\n", x, y, z);
}

template <typename T>
Math::Vector<T>
Math::calcNormal(const Vector<T>& a, const Vector<T>& b) {
    return a.crossProduct(b).normalize();
}
