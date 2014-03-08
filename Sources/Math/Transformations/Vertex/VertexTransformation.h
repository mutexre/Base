#ifndef header_A22F5D9F9ED3
#define header_A22F5D9F9ED3

namespace Math
{
    template <typename T>
    class VertexTransformation
    {
    public:
        virtual void transform(const Vertex<T>& input, Vertex<T>& output) = 0;
        virtual void transform(const Vertex<T>* input, Vertex<T>& output);
        virtual void transform(const Vertex<T>& input, Vertex<T>* output);
        virtual void transform(const Vertex<T>* input, Vertex<T>* output);
    };

    #include <Math/Transformations/Vertex/VertexTransformationDefinition.h>
}

#endif
