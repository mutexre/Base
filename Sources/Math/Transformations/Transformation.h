#ifndef header_A72B2D692F98
#define header_A72B2D692F98

namespace Math
{
    template <typename T, unsigned char inN, unsigned char outN>
    class Transformation
    {
    public:
        virtual void transform(const T input[inN], T output[outN]) = 0;
    };
}

#endif
