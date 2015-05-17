//
//  GCD.h
//  Math
//
//  Created by mutexre on 17/05/15.
//
//

#ifndef Math_GCD_h
#define Math_GCD_h

namespace Math
{
    template <typename T = Rt::u4>
    inline T gcd(T a, T b)
    {
        while (b) b^=a^=b^=a%=b;
        return a; 
    }

    template <typename T = Rt::u4>
    inline T gcd2(T a, T b)
    {
        T c;
        while (b) {
            c = a % b;
            a = b;
            b = c;
        }
        return abs(a);
    }

    template <typename T = Rt::u4>
    inline T gcd3(T u, T v)
    {
        Rt::u1 shift;

        if (u == 0 || v == 0) return u | v;

        /* Let shift := lg K, where K is the greatest power of 2 dividing both u and v. */
        for (shift = 0; ((u | v) & 1) == 0; ++shift) {
            u >>= 1;
            v >>= 1;
        }

        while ((u & 1) == 0) u >>= 1;

        /* From here on, u is always odd. */
        do {
            /* Loop X */
            while ((v & 1) == 0) v >>= 1;

            /* Now u and v are both odd, so diff(u, v) is even. Let u = min(u, v), v = diff(u, v)/2. */
            if (u < v)
                v -= u;
            else {
                T diff = u - v;
                u = v;
                v = diff;
            }

            v >>= 1;
        }
        while (v != 0);

        return u << shift;
    }
}

#endif
