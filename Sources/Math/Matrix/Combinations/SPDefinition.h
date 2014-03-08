template <typename T>
SP<T>::SP() : order(Order::kSP),
                       sx(T(1)), sy(T(1)), sz(T(1)),
                       fieldOfView(T(2) * M_PI / T(6)), nearZ(T(1)), farZ(T(10))
{
    this->setMatrixValid(false);
}

template <typename T>
SP<T>::SP(Order order,
                   T sx, T sy, T sz,
                   T fieldOfView, T nearZ, T farZ)
{
    this->setMatrixValid(false);

    this->order = order;

    this->sx = sx;
    this->sy = sy;
    this->sz = sz;

    this->fieldOfView = fieldOfView;
    this->nearZ = nearZ;
    this->farZ = farZ;
}

template <typename T>
typename SP<T>::Order SP<T>::getOrder() const {
    return order;
}

template <typename T>
void SP<T>::setOrder(Order order) {
    this->order = order;
}

template <typename T>
void SP<T>::getScale(T& sx, T& sy, T& sz) const {
    sx = this->sx;
    sy = this->sy;
    sz = this->sz;
}

template <typename T>
void SP<T>::setScale(T sx, T sy, T sz) {
    this->setMatrixValid(false);
    this->sx = sx;
    this->sy = sy;
    this->sz = sz;
}

template <typename T>
T SP<T>::getSX() const {
    return sx;
}

template <typename T>
void SP<T>::setSX(T sx) {
    this->setMatrixValid(false);
    this->sx = sx;
}

template <typename T>
T SP<T>::getSY() const {
    return sy;
}

template <typename T>
void SP<T>::setSY(T sy) {
    this->setMatrixValid(false);
    this->sy = sy;
}

template <typename T>
T SP<T>::getSZ() const {
    return sz;
}

template <typename T>
void SP<T>::setSZ(T sz) {
    this->setMatrixValid(false);
    this->sz = sz;
}

template <typename T>
void SP<T>::__setFieldOfView(T value) {
    fieldOfView = value;
    this->f = T(1) / tanf((T(1) / T(2)) * value);
}

template <typename T>
void SP<T>::getPerspective(T& fieldOfView, T& nearZ, T& farZ) const {
    fieldOfView = this->fieldOfView;
    nearZ = this->nearZ;
    farZ = this->farZ;
}

template <typename T>
void SP<T>::setPerspective(T fieldOfView, T nearZ, T farZ) {
    this->setMatrixValid(false);

    __setFieldOfView(fieldOfView);
    this->nearZ = nearZ;
    this->farZ = farZ;
}

template <typename T>
T SP<T>::getFieldOfView() const
{
    return fieldOfView;
}

template <typename T>
void SP<T>::setFieldOfView(T value)
{
    this->setMatrixValid(false);
    __setFieldOfView(value);
}

template <typename T>
T SP<T>::getNearZ() const
{
    return nearZ;
}

template <typename T>
void SP<T>::setNearZ(T value)
{
    this->setMatrixValid(false);
    nearZ = value;
}

template <typename T>
T SP<T>::getFarZ() const
{
    return farZ;
}

template <typename T>
void SP<T>::setFarZ(T value)
{
    this->setMatrixValid(false);
    farZ = value;
}

template <typename T>
void SP<T>::calcMatrixSP()
{
    auto sxf = sx * f;
    auto syf = sy * f;
    auto far_plus_near = farZ + nearZ;
    auto inv_near_minus_far = T(1) / (nearZ - farZ);

    element(this->matrix, 0, 0, 4) = sxf;
    element(this->matrix, 0, 1, 4) = T(0);
    element(this->matrix, 0, 2, 4) = T(0); 
    element(this->matrix, 0, 3, 4) = T(0);

    element(this->matrix, 1, 0, 4) = T(0);
    element(this->matrix, 1, 1, 4) = syf;
    element(this->matrix, 1, 2, 4) = T(0);
    element(this->matrix, 1, 3, 4) = T(0);

    element(this->matrix, 2, 0, 4) = T(0);
    element(this->matrix, 2, 1, 4) = T(0);
    element(this->matrix, 2, 2, 4) = sz * far_plus_near * inv_near_minus_far;
    element(this->matrix, 2, 3, 4) = T(2) * farZ * nearZ * inv_near_minus_far;

    element(this->matrix, 3, 0, 4) = T(0);
    element(this->matrix, 3, 1, 4) = T(0);
    element(this->matrix, 3, 2, 4) = -sz;
    element(this->matrix, 3, 3, 4) = T(1);
}

template <typename T>
void SP<T>::calcMatrixPS()
{
    auto sxf = sx * f;
    auto syf = sy * f;
    auto far_plus_near = farZ + nearZ;
    auto inv_near_minus_far = T(1) / (nearZ - farZ);

    element(this->matrix, 0, 0, 4) = sxf;
    element(this->matrix, 0, 1, 4) = T(0);
    element(this->matrix, 0, 2, 4) = T(0); 
    element(this->matrix, 0, 3, 4) = T(0);

    element(this->matrix, 1, 0, 4) = T(0);
    element(this->matrix, 1, 1, 4) = syf;
    element(this->matrix, 1, 2, 4) = T(0);
    element(this->matrix, 1, 3, 4) = T(0);

    element(this->matrix, 2, 0, 4) = T(0);
    element(this->matrix, 2, 1, 4) = T(0);
    element(this->matrix, 2, 2, 4) = sz * far_plus_near * inv_near_minus_far;
    element(this->matrix, 2, 3, 4) = T(2) * farZ * nearZ * inv_near_minus_far;

    element(this->matrix, 3, 0, 4) = T(0);
    element(this->matrix, 3, 1, 4) = T(0);
    element(this->matrix, 3, 2, 4) = -sz;
    element(this->matrix, 3, 3, 4) = T(1);
}

template <typename T>
void SP<T>::calcMatrix()
{
    switch (order) {
        case Order::kSP: calcMatrixSP(); break;
        case Order::kPS: calcMatrixPS(); break;
    }

    this->setMatrixValid(true);
}
