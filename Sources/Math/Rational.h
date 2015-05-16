#ifndef header_C9E159688D8B
#define header_C9E159688D8B

namespace Math
{
    template <typename T = Rt::u4>
    class Rational
    {
    public:
        T a, b;

        Rational() { a = 0; b = 1; }
        Rational(T n) { a = n; b = 1; }
        Rational(T a, T b) { this->a = a; this->b = b; }
        Rational(float f) { *this = float2rational(f); }

        Rational& operator=(T n) { a = n; b = 1; return *this; }

        Rational& operator+=(const Rational& rational);
        Rational& operator-=(const Rational& rational);
        Rational& operator*=(const Rational& rational);
        Rational& operator/=(const Rational& rational);

        Rational& add(const Rational& rational);
        Rational& sub(const Rational& rational);
        Rational& mul(const Rational& rational);
        Rational& div(const Rational& rational);

        Rational& operator+=(T n);
        Rational& operator-=(T n);
        Rational& operator*=(T n);
        Rational& operator/=(T n);

        Rational& add(T n);
        Rational& sub(T n);
        Rational& mul(T n);
        Rational& div(T n);

        Rational operator+(const Rational& rational);
        Rational operator-(const Rational& rational);
        Rational operator*(const Rational& rational);
        Rational operator/(const Rational& rational);

        const Rational& operator++();
        const Rational& operator--();

        bool operator!() const { return !a; }

        bool operator<(const Rational& rational) const;
        bool operator>(const Rational& rational) const;
        bool operator==(const Rational& rational) const;

        bool operator<(T n) const;
        bool operator>(T n) const;
        bool operator==(T n) const;

        static Rational float2rational(float f);
        template <typename P> P cast() { return static_cast<P>(a) / static_cast<P>(b); }

        void normalize();
    };

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

    #include <Math/RationalDefinition.h>
}

#endif
