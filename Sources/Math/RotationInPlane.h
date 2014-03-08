#ifndef header_D16BC87DDAC0
#define header_D16BC87DDAC0

namespace Math
{
    template <typename T = float, typename D = Rt::u1>
    struct RotationInPlane
    {
    private:
        void calcSinCos() {
            sin = std::sin(angle);
            cos = std::cos(angle);
        }

    public:
        D dim[2];
        T angle, sin, cos;

    public:
        RotationInPlane() {}

        RotationInPlane(D dim0, D dim1, T angle) {
            dim[0] = dim0;
            dim[1] = dim1;
            this->angle = angle;
            calcSinCos();
        }

        void setAngle(T angle) {
            this->angle = angle;
            calcSinCos();
        }
    };
}

#endif
