#ifndef header_995D9B2208ED
#define header_995D9B2208ED

namespace Math
{
    template <typename T> class Vector;

    template <typename T>
    class Vertex
    {
    public:
        T x, y, z, w;

        Vertex();
        Vertex(const Vertex<T>& v);
        Vertex(const Vertex<T>* v);
        Vertex(const Vector<T>& v);
        Vertex(const Vector<T>* v);

        Vertex<T>& operator-(Vertex<T>& v);
        Vertex<T>& operator+(Vertex<T>& v);

        void print() const;
    };
}

#endif
