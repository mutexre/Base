#ifndef header_3A892E8A7B94
#define header_3A892E8A7B94

namespace Math
{
    template <typename T = float>
    class TSP : public VertexMatrixTransformation<T>
    {
    public:
        enum class Order
        {
            kTSP,
            kTPS,
            kSTP,
            kSPT,
            kPTS,
            kPST
        };

    private:
        Order order;
        T dx, dy, dz;
        T sx, sy, sz;
        T fieldOfView, nearZ, farZ, f;

        void __setFieldOfView(T);

        void calcMatrixTSP();
        void calcMatrixTPS();
        void calcMatrixSTP();
        void calcMatrixSPT();
        void calcMatrixPTS();
        void calcMatrixPST();

    public:
        TSP();
        TSP(Order order,
            T dx, T dy, T dz,
            T sx, T sy, T sz,
            T fieldOfView, T nearZ, T farZ);

        Order getOrder() const;
        void setOrder(Order);

        void getTranslation(T& dx, T& dy, T& dz) const;
        void setTranslation(T dx, T dy, T dz);

        T getDX() const;
        void setDX(T);

        T getDY() const;
        void setDY(T);

        T getDZ() const;
        void setDZ(T);

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

    #include <Math/Transformations/Matrix/Square/Vertex/Special/Combinations/TSPDefinition.h>
}

#endif
