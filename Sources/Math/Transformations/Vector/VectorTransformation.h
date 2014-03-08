#ifndef header_E7BDC5A97B46
#define header_E7BDC5A97B46

#include <Math/Vector.h>

namespace Math
{
    template <typename T>
    class VectorTransformation
    {
    public:
        virtual void transform(const Vertex<T>& vertex, const Vector<T>& input, Vector<T>& output) = 0;
        virtual void transform(const Vertex<T>& vertex, const Vector<T>* input, Vector<T>& output);
        virtual void transform(const Vertex<T>& vertex, const Vector<T>& input, Vector<T>* output);
        virtual void transform(const Vertex<T>& vertex, const Vector<T>* input, Vector<T>* output);
        virtual void transform(const Vertex<T>* vertex, const Vector<T>& input, Vector<T>& output);
        virtual void transform(const Vertex<T>* vertex, const Vector<T>* input, Vector<T>& output);
        virtual void transform(const Vertex<T>* vertex, const Vector<T>& input, Vector<T>* output);
        virtual void transform(const Vertex<T>* vertex, const Vector<T>* input, Vector<T>* output);
    };

    #include <Math/Transformations/Vector/VectorTransformationDefinition.h>
}

#endif
