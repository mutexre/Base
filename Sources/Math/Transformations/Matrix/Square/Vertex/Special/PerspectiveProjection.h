#ifndef header_F81EC71134F2
#define header_F81EC71134F2

namespace Math
{
    template <typename T>
    class PerspectiveProjection : public VertexMatrixTransformation<T>
    {
    private:
        T fieldOfView;
        T nearZ;
        T farZ;
        T f;

        void __setFieldOfView(T);

    public:
        PerspectiveProjection();
        PerspectiveProjection(T fieldOfView, T nearZ, T farZ);

        void get(T& fieldOfView, T& nearZ, T& farZ) const;
        void set(T fieldOfView, T nearZ, T farZ);

        T getFieldOfView() const;
        void setFieldOfView(T);

        T getNear() const;
        void setNear(T);

        T getFar() const;
        void setFar(T);

        virtual void transform(const Vertex<T>& vertex, const Plane<T>& input, Plane<T>& output);

        void calcMatrix();
    };

    #include <Math/Transformations/Matrix/Square/Vertex/Special/PerspectiveProjectionDefinition.h>
}

#endif
