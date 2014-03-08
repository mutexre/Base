#ifndef header_E6DF6434ABE8
#define header_E6DF6434ABE8

namespace Math
{
    template <typename T = float>
    class OrthogonalProjection : public Matrix<T>
    {
    private:
        struct { T x, y, z; } min, max, middle, size;

    public:
        OrthogonalProjection();
        OrthogonalProjection(T minX, T maxX, T minY, T maxY, T minZ, T maxZ);

        virtual void transform(const Vertex<T>& vertex, const Plane<T>& input, Plane<T>& output);
        void calcMatrix();
    };

    #include <Math/Matrix/OrthogonalProjectionDefinition.h>
}

#endif
