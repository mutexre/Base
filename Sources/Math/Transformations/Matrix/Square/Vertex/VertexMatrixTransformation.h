#ifndef header_4E01D7A18839
#define header_4E01D7A18839

namespace Math
{
    template <typename T>
    class VertexMatrixTransformation : public SquareMatrix4<T>,
                                       public VertexTransformation<T>
                                       //public PlaneTransformation<T>
    {
    public:
        virtual void transform(const Vertex<T>& input, Vertex<T>& output);
    };

    #include <Math/Transformations/Matrix/Square/Vertex/VertexMatrixTransformationDefinition.h>
}

#endif
