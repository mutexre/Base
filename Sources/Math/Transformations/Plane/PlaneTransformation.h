#ifndef header_1278438E03C7
#define header_1278438E03C7

namespace Math
{
    template <typename T>
    class PlaneTransformation
    {
    public:
        virtual void transform(const Vertex<T>& vertex, const Plane<T>& input, Plane<T>& output) = 0;
        virtual void transform(const Vertex<T>& vertex, const Plane<T>* input, Plane<T>& output);
        virtual void transform(const Vertex<T>& vertex, const Plane<T>& input, Plane<T>* output);
        virtual void transform(const Vertex<T>& vertex, const Plane<T>* input, Plane<T>* output);
        virtual void transform(const Vertex<T>* vertex, const Plane<T>& input, Plane<T>& output);
        virtual void transform(const Vertex<T>* vertex, const Plane<T>* input, Plane<T>& output);
        virtual void transform(const Vertex<T>* vertex, const Plane<T>& input, Plane<T>* output);
        virtual void transform(const Vertex<T>* vertex, const Plane<T>* input, Plane<T>* output);
    };

    #include <Math/Transformations/Plane/PlaneTransformationDefinition.h>
}

#endif
