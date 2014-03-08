template <typename T>
void VectorTransformation<T>::transform(const Vertex<T>& vertex, const Vector<T>* input, Vector<T>& output) {
    transform(vertex, *input, output);
}

template <typename T>
void VectorTransformation<T>::transform(const Vertex<T>& vertex, const Vector<T>& input, Vector<T>* output) {
    transform(vertex, input, *output);
}

template <typename T>
void VectorTransformation<T>::transform(const Vertex<T>& vertex, const Vector<T>* input, Vector<T>* output) {
    transform(vertex, *input, *output);
}

template <typename T>
void VectorTransformation<T>::transform(const Vertex<T>* vertex, const Vector<T>& input, Vector<T>& output) {
    transform(*vertex, input, output);
}

template <typename T>
void VectorTransformation<T>::transform(const Vertex<T>* vertex, const Vector<T>* input, Vector<T>& output) {
    transform(*vertex, *input, output);
}

template <typename T>
void VectorTransformation<T>::transform(const Vertex<T>* vertex, const Vector<T>& input, Vector<T>* output) {
    transform(*vertex, input, *output);
}

template <typename T>
void VectorTransformation<T>::transform(const Vertex<T>* vertex, const Vector<T>* input, Vector<T>* output) {
    transform(*vertex, *input, *output);
}
