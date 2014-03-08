#ifndef header_E21080B1E255
#define header_E21080B1E255

namespace Math
{
    template <typename T>
    class SP : public VertexMatrixTransformation<T>
    {
    public:
        enum class Order {
            kSP,
            kPS
        };

    private:
        Order order;
        T sx, sy, sz;
        T fieldOfView, nearZ, farZ, f;

        void __setFieldOfView(T);

        void calcMatrixSP();
        void calcMatrixPS();

    public:
        SP();
        SP(Order order,
           T sx, T sy, T sz,
           T fieldOfView, T nearZ, T farZ);

        Order getOrder() const;
        void setOrder(Order);

        void getScale(T& sx, T& sy, T& sz) const;
        void setScale(T sx, T sy, T sz);

        T getSX() const;
        void setSX(T);

        T getSY() const;
        void setSY(T);

        T getSZ() const;
        void setSZ(T);

        void getPerspective(T& fieldOfView, T& nearZ, T& farZ) const;
        void setPerspective(T fieldOfView, T nearZ, T farZ);

        T getFieldOfView() const;
        void setFieldOfView(T);

        T getNearZ() const;
        void setNearZ(T);

        T getFarZ() const;
        void setFarZ(T);

        virtual void calcMatrix();
    };

    #include <Math/Transformations/Matrix/Square/Vertex/Special/Combinations/SPDefinition.h>
}

#endif
