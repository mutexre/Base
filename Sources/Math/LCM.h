#ifndef Math_LCM_h
#define Math_LCM_h

namespace Math
{
    template <typename T = Rt::u4>
    inline T lcm(T a, T b)
    {
        return a / gcd(a, b) * b;
    }

    template <typename T = Rt::u4>
    inline T lcm2(T a, T b)
    {
        return a / gcd2(a, b) * b;
    }

    template <typename T = Rt::u4>
    inline T lcm3(T a, T b)
    {
        return a / gcd3(a, b) * b;
    }
}

#endif
