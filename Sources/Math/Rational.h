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
        bool operator<=(const Rational& rational) const;
        bool operator>(const Rational& rational) const;
        bool operator>=(const Rational& rational) const;
        bool operator==(const Rational& rational) const;

        bool operator<(T n) const;
        bool operator<=(T n) const;
        bool operator>(T n) const;
        bool operator>=(T n) const;
        bool operator==(T n) const;

        static Rational float2rational(float f);
        template <typename P> P cast() { return static_cast<P>(a) / static_cast<P>(b); }

        void normalize();
    };

    template <typename T = int>
    Rational<T> operator+(const Rational<T>& x, const Rational<T>& y) {
        return Rational<T>(x.a * y.b + x.b * y.a, x.b * y.b);
    }

    template <typename T = int>
    Rational<T> operator-(const Rational<T>& x, const Rational<T>& y) {
        return Rational<T>(x.a * y.b - x.b * y.a, x.b * y.b);
    }

    template <typename T = int>
    Rational<T> operator*(const Rational<T>& x, const Rational<T>& y) {
        return Rational<T>(x.a * y.a, x.b * y.b);
    }

    template <typename T = int>
    Rational<T> operator/(const Rational<T>& x, const Rational<T>& y) {
        return Rational<T>(x.a * y.b, x.b * y.a);
    }

    #include <Math/RationalDefinition.h>
}

#endif
