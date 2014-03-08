template <typename T>
Rt::Value::Container<T>::~Container() {}

template <typename T>
T& Rt::Value::Container<T>::getContainer() {
    return container;
}

template <typename T>
bool Rt::Value::Container<T>::isEmpty() {
    return container.empty();
}

template <typename T>
void Rt::Value::Container<T>::clear() {
    container.clear();
    incrementVersion();
    notify(this);
}
