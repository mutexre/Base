template <typename T>
TSP<T>::TSP() : order(Order::kTSP),
                         dx(T(0)), dy(T(0)), dz(T(0)),
                         sx(T(1)), sy(T(1)), sz(T(1)),
                         fieldOfView(T(2) * M_PI / T(6)), nearZ(T(1)), farZ(T(10))
{
    this->setMatrixValid(false);
}

template <typename T>
TSP<T>::TSP(Order order,
                     T dx, T dy, T dz,
                     T sx, T sy, T sz,
                     T fieldOfView, T nearZ, T farZ)
{
    this->setMatrixValid(false);

    this->order = order;

    this->dx = dx;
    this->dy = dy;
    this->dz = dz;

    this->sx = sx;
    this->sy = sy;
    this->sz = sz;

    this->fieldOfView = fieldOfView;
    this->nearZ = nearZ;
    this->farZ = farZ;
}

template <typename T>
typename TSP<T>::Order TSP<T>::getOrder() const
{
    return order;
}

template <typename T>
void TSP<T>::setOrder(Order order)
{
    this->order = order;
}

template <typename T>
void TSP<T>::getTranslation(T& dx, T& dy, T& dz) const
{
    dx = this->dx;
    dy = this->dy;
    dz = this->dz;
}

template <typename T>
void TSP<T>::setTranslation(T dx, T dy, T dz)
{
    this->setMatrixValid(false);
    this->dx = dx;
    this->dy = dy;
    this->dz = dz;
}

template <typename T>
T TSP<T>::getDX() const
{
    return dx;
}

template <typename T>
void TSP<T>::setDX(T dx)
{
    this->setMatrixValid(false);
    this->dx = dx;
}

template <typename T>
T TSP<T>::getDY() const
{
    return dy;
}

template <typename T>
void TSP<T>::setDY(T dy)
{
    this->setMatrixValid(false);
    this->dy = dy;
}

template <typename T>
T TSP<T>::getDZ() const
{
    return dz;
}

template <typename T>
void TSP<T>::setDZ(T dz)
{
    this->setMatrixValid(false);
    this->dz = dz;
}

template <typename T>
void TSP<T>::getScale(T& sx, T& sy, T& sz) const
{
    sx = this->sx;
    sy = this->sy;
    sz = this->sz;
}

template <typename T>
void TSP<T>::setScale(T sx, T sy, T sz)
{
    this->setMatrixValid(false);
    this->sx = sx;
    this->sy = sy;
    this->sz = sz;
}

template <typename T>
T TSP<T>::getSX() const
{
    return sx;
}

template <typename T>
void TSP<T>::setSX(T sx)
{
    this->setMatrixValid(false);
    this->sx = sx;
}

template <typename T>
T TSP<T>::getSY() const
{
    return sy;
}

template <typename T>
void TSP<T>::setSY(T sy)
{
    this->setMatrixValid(false);
    this->sy = sy;
}

template <typename T>
T TSP<T>::getSZ() const
{
    return sz;
}

template <typename T>
void TSP<T>::setSZ(T sz)
{
    this->setMatrixValid(false);
    this->sz = sz;
}

template <typename T>
void TSP<T>::__setFieldOfView(T value)
{
    fieldOfView = value;
    this->f = T(1) / tanf((T(1) / T(2)) * value);
}

template <typename T>
void TSP<T>::getPerspective(T& fieldOfView, T& nearZ, T& farZ) const
{
    fieldOfView = this->fieldOfView;
    nearZ = this->nearZ;
    farZ = this->farZ;
}

template <typename T>
void TSP<T>::setPerspective(T fieldOfView, T nearZ, T farZ)
{
    this->setMatrixValid(false);

    __setFieldOfView(fieldOfView);
    this->nearZ = nearZ;
    this->farZ = farZ;
}

template <typename T>
T TSP<T>::getFieldOfView() const
{
    return fieldOfView;
}

template <typename T>
void TSP<T>::setFieldOfView(T value)
{
    this->setMatrixValid(false);
    __setFieldOfView(value);
}

template <typename T>
T TSP<T>::getNearZ() const
{
    return nearZ;
}

template <typename T>
void TSP<T>::setNearZ(T value)
{
    this->setMatrixValid(false);
    nearZ = value;
}

template <typename T>
T TSP<T>::getFarZ() const
{
    return farZ;
}

template <typename T>
void TSP<T>::setFarZ(T value)
{
    this->setMatrixValid(false);
    farZ = value;
}

template <typename T>
void TSP<T>::calcMatrixTSP()
{
    auto sxf = sx * f;
    auto syf = sy * f;
    auto far_plus_near = farZ + nearZ;
    auto inv_near_minus_far = T(1) / (nearZ - farZ);

    element(this->matrix, 0, 0, 4) = sxf;
    element(this->matrix, 0, 1, 4) = T(0);
    element(this->matrix, 0, 2, 4) = T(0); 
    element(this->matrix, 0, 3, 4) = sxf * dx;

    element(this->matrix, 1, 0, 4) = T(0);
    element(this->matrix, 1, 1, 4) = syf;
    element(this->matrix, 1, 2, 4) = T(0);
    element(this->matrix, 1, 3, 4) = syf * dy;

    element(this->matrix, 2, 0, 4) = T(0);
    element(this->matrix, 2, 1, 4) = T(0);
    element(this->matrix, 2, 2, 4) = sz * far_plus_near * inv_near_minus_far;
    element(this->matrix, 2, 3, 4) = (T(2) * farZ * nearZ + far_plus_near * sz * dz) * inv_near_minus_far;

    element(this->matrix, 3, 0, 4) = T(0);
    element(this->matrix, 3, 1, 4) = T(0);
    element(this->matrix, 3, 2, 4) = -sz;
    element(this->matrix, 3, 3, 4) = T(1) - sz * dz;
}

template <typename T>
void TSP<T>::calcMatrixTPS(){
}

template <typename T>
void TSP<T>::calcMatrixSTP(){
}

template <typename T>
void TSP<T>::calcMatrixSPT(){
}

template <typename T>
void TSP<T>::calcMatrixPTS(){
}

template <typename T>
void TSP<T>::calcMatrixPST(){
}

template <typename T>
void TSP<T>::calcMatrix()
{
    switch (order)
    {
        case Order::kTSP: calcMatrixTSP(); break;
        case Order::kTPS: calcMatrixTPS(); break;
        case Order::kSTP: calcMatrixSTP(); break;
        case Order::kSPT: calcMatrixSPT(); break;
        case Order::kPTS: calcMatrixPTS(); break;
        case Order::kPST: calcMatrixPST(); break;
    }

    this->setMatrixValid(true);
}
