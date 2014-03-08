#ifndef header_AA37507AFEF9
#define header_AA37507AFEF9

#include <math.h>

namespace Math
{
    template <typename T>
    class Rotation : public VertexMatrixTransformation<T>
    {
    private:
        static T f0(T x, T c, T one_minus_c);
        static T f1(T x, T y, T z, T c, T s);

        void calcRotationMatrix(T x, T y, T z, T angle);

    public:
        Rotation();
        Rotation(T x, T y, T z, T angle, bool normalize = true);
    };

    #include <Math/Transformations/Matrix/Square/Vertex/Special/RotationDefinition.h>
}

#endif
