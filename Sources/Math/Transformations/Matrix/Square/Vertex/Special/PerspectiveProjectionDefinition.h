#include <math.h>

template <typename T>
void PerspectiveProjection<T>::__setFieldOfView(T value) {
    fieldOfView = value;
    this->f = T(1) / tanf(0.5f * value);
}

template <typename T>
PerspectiveProjection<T>::PerspectiveProjection()
{}

template <typename T>
PerspectiveProjection<T>::PerspectiveProjection(T fieldOfView, T nearZ, T farZ) {
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

    element(this->matrix, 0, 0, 4) = -f;
    element(this->matrix, 1, 1, 4) = -f;
    element(this->matrix, 2, 2, 4) = (farZ + nearZ) * inv_near_minus_far;
    element(this->matrix, 3, 3, 4) = T(0);

    if (this->layout == MatrixLayout::RowMajor) {
        element(this->matrix, 3, 2, 4) = -T(1);
        element(this->matrix, 2, 3, 4) = T(2) * farZ * nearZ * inv_near_minus_far;
    }
    else {
        element(this->matrix, 2, 3, 4) = -T(1);
        element(this->matrix, 2, 2, 4) = T(2) * farZ * nearZ * inv_near_minus_far;
    }
}
