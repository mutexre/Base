template <typename T>
void PlaneTransformation<T>::transform(const Vertex<T>& vertex, const Plane<T>* input, Plane<T>& output) {
    transform(vertex, *input, output);
}

template <typename T>
void PlaneTransformation<T>::transform(const Vertex<T>& vertex, const Plane<T>& input, Plane<T>* output) {
    transform(vertex, input, *output);
}

template <typename T>
void PlaneTransformation<T>::transform(const Vertex<T>& vertex, const Plane<T>* input, Plane<T>* output) {
    transform(vertex, *input, *output);
}

template <typename T>
void PlaneTransformation<T>::transform(const Vertex<T>* vertex, const Plane<T>& input, Plane<T>& output) {
    transform(*vertex, input, output);
}

template <typename T>
void PlaneTransformation<T>::transform(const Vertex<T>* vertex, const Plane<T>* input, Plane<T>& output) {
    transform(*vertex, *input, output);
}

template <typename T>
void PlaneTransformation<T>::transform(const Vertex<T>* vertex, const Plane<T>& input, Plane<T>* output) {
    transform(*vertex, input, *output);
}

template <typename T>
void PlaneTransformation<T>::transform(const Vertex<T>* vertex, const Plane<T>* input, Plane<T>* output) {
    transform(*vertex, *input, *output);
}
