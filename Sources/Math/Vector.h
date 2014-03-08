#ifndef header_A6F46E99F963
#define header_A6F46E99F963

namespace Math
{
    template <typename T> class Vertex;

    template <typename T>
    class Vector
    {
    public:
        T x, y, z;

        Vector();
        Vector(T);
        Vector(T x, T y, T z);
        Vector(const Vector<T>&);
        Vector(const Vector<T>*);
        Vector(const Vertex<T>&);
        Vector(const Vertex<T>*);

//        static Vector<T> operator-(const Vector<T>& a, const Vector<T>& b);

//        Vector<T>& operator-(const Vector<T>&);
        Vector<T> operator-(const Vector<T>&) const;

        Vector<T>& operator+(const Vector<T>&);

        Vector<T>& operator*(T);
        Vector<T>& operator/(T);

        Vector<T>& operator-=(const Vector<T>&);
        Vector<T>& operator+=(const Vector<T>&);

        Vector<T>& operator*=(T);
        Vector<T>& operator/=(T);

        Vector<T>& operator=(T);

        T operator*(const Vector<T>&);

        T powOf2OfLength() const;
        T length() const;

        T scalarProduct(const Vector<T>& that) const;
        Vector<T> crossProduct(const Vector<T>& that) const;

        Vector<T>& normalize();

//        Vector2D projectToPlane(Plane& p);
//        Scalar projectToVector(Vector);

        void print() const;
    };

    template <typename T>
    Vector<T> calcNormal(const Vector<T>& a, const Vector<T>& b);
}

#endif
