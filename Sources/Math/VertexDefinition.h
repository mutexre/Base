#include <Math/Vertex.h>
#include <Math/Vector.h>

template <typename T>
Math::Vertex<T>::Vertex()
{}

template <typename T>
Math::Vertex<T>::Vertex(const Vertex<T>& v) : x(v.x), y(v.y), z(v.z), w(v.w)
{}

template <typename T>
Math::Vertex<T>::Vertex(const Vertex<T>* v) : x(v->x), y(v->y), z(v->z), w(v->w)
{}

template <typename T>
Math::Vertex<T>::Vertex(const Vector<T>& v) : x(v.x), y(v.y), z(v.z), w(1.0)
{}

template <typename T>
Math::Vertex<T>::Vertex(const Vector<T>* v) : x(v->x), y(v->y), z(v->z), w(1.0)
{}

template <typename T>
Math::Vertex<T>& Math::Vertex<T>::operator-(Vertex<T>& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

template <typename T>
Math::Vertex<T>& Math::Vertex<T>::operator+(Vertex<T>& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

template <typename T>
void Math::Vertex<T>::print() const {
    printf("%f %f %f %f\n", x, y, z, w);
}
