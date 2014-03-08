template <typename T>
Degenerate<T>::Degenerate(T value) {
    this->value = value;
    range = Range<T>(value, T(0));
}

template <typename T>
T Degenerate<T>::sample() {
    return value;
}

template <typename T>
Rt::Option<Rt::Range<T>>
Degenerate<T>::getRange() {
    return Option<Range<T>>(range);
}
