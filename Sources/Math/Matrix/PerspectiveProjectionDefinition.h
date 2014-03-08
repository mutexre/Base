#include <math.h>

template <typename T>
void PerspectiveProjection<T>::__setFieldOfView(T value) {
    fieldOfView = value;
    this->f = T(1) / tanf(0.5f * value);
}

template <typename T>
PerspectiveProjection<T>::PerspectiveProjection() {
    this->initSquareMatrix(4);
    this->data.resize(4 * 4);
}

template <typename T>
PerspectiveProjection<T>::PerspectiveProjection(T fieldOfView, T nearZ, T farZ) {
    this->initSquareMatrix(4);
    this->data.resize(4 * 4);
    setFieldOfView(fieldOfView);
    setNear(nearZ);
    setFar(farZ);
    calcMatrix();
}

template <typename T>
void PerspectiveProjection<T>::get(T& fieldOfView, T& nearZ, T& farZ) const {
    fieldOfView = this->fieldOfView;
    nearZ = this->nearZ;
    farZ = this->farZ;
}

template <typename T>
void PerspectiveProjection<T>::set(T fieldOfView, T nearZ, T farZ) {
    __setFieldOfView(fieldOfView);
    this->nearZ = nearZ;
    this->farZ = farZ;
}

template <typename T>
T PerspectiveProjection<T>::getFieldOfView() const {
    return fieldOfView;
}

template <typename T>
void PerspectiveProjection<T>::setFieldOfView(T value) {
    __setFieldOfView(value);
}

template <typename T>
T PerspectiveProjection<T>::getNear() const {
    return nearZ;
}

template <typename T>
void PerspectiveProjection<T>::setNear(T value) {
    nearZ = value;
}

template <typename T>
T PerspectiveProjection<T>::getFar() const {
    return farZ;
}

template <typename T>
void PerspectiveProjection<T>::setFar(T value) {
    farZ = value;
}

template <typename T>
void PerspectiveProjection<T>::transform(const Vertex<T>& vertex,
                                         const Plane<T>& input,
                                         Plane<T>& output)
{
    float beta = T(2) * farZ * nearZ / (farZ - nearZ);

    output.a = input.a * beta;
    output.b = input.b * beta;
    output.c = input.d * f;
    output.d = T(0);
}

template <typename T>
void PerspectiveProjection<T>::calcMatrix()
{
    auto inv_near_minus_far = T(1) / (nearZ - farZ);

    this->loadIdentity();
    this->Matrix<T>::set(0, 0, -f);
    this->Matrix<T>::set(1, 1, -f);
    this->Matrix<T>::set(2, 2, (farZ + nearZ) * inv_near_minus_far);
    this->Matrix<T>::set(3, 3, T(0));
    this->Matrix<T>::set(3, 2, -T(1));
    this->Matrix<T>::set(2, 3, T(2) * farZ * nearZ * inv_near_minus_far);
}
