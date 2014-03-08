#ifndef header_73BCADEB4395
#define header_73BCADEB4395

namespace Math
{
    template <typename T>
    class Scale : public VertexMatrixTransformation<T>
    {
    private:
        T x;
        T y;
        T z;

    public:
        Scale();
        Scale(T x, T y, T z);

        void getXYZ(T& x, T& y, T& z) const;
        void setXYZ(T x, T y, T z);

        T getX() const;
        void setX(T);

        T getY() const;
        void setY(T);

        T getZ() const;
        void setZ(T);

        virtual void calcMatrix();
    };

    #include <Math/Transformations/Matrix/Square/Vertex/Special/ScaleDefinition.h>
}

#endif
