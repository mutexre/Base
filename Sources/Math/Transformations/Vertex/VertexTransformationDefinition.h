template <typename T>
void VertexTransformation<T>::transform(const Vertex<T>* input, Vertex<T>& output) {
    transform(*input, output);
}

template <typename T>
void VertexTransformation<T>::transform(const Vertex<T>& input, Vertex<T>* output) {
    transform(input, *output);
}

template <typename T>
void VertexTransformation<T>::transform(const Vertex<T>* input, Vertex<T>* output) {
    transform(*input, *output);
}
