#ifndef header_FA2192924FAE
#define header_FA2192924FAE

namespace Math
{
    template <typename T = float>
    class Translation : public Matrix<T>
    {
    private:
        T x;
        T y;
        T z;

    public:
        Translation();
        Translation(T x, T y, T z);

        void get(T& x, T& y, T& z) const;
        void set(T x, T y, T z);

        T getX() const;
        void setX(T);

        T getY() const;
        void setY(T);

        T getZ() const;
        void setZ(T);

        virtual void calcMatrix();
    };

    #include <Math/Matrix/TranslationDefinition.h>
}

#endif
