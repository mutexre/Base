template <typename T>
Rt::Value::Scalar<T>::Scalar() {
    this->invalidate();
}

template <typename T>
Rt::Value::Scalar<T>::Scalar(T value) : Trait(Type::Scalar) {
    this->value = value;
    this->setValidity(true);
}

template <typename T>
T& Rt::Value::Scalar<T>::get() {
    evaluateIfNeeded();
    return value;
}

template <typename T>
void Rt::Value::Scalar<T>::set(T value) {
    this->value = value;
}
