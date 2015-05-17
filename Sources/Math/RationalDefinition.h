template <typename T>
inline Rational<T> operator+ (const Rational<T>& rational)
{
    return rational;
}

template <typename T>
inline Rational<T> operator- (const Rational<T>& rational)
{
    return Rational<T>(-rational.a, rational.b);
}

template <typename T>
inline Rational<T>& Rational<T>::operator+=(const Rational& rational)
{
    a = a * rational.b - b * rational.a;
    b = b * rational.b;
    return *this;
}

template <typename T>
inline Rational<T>& Rational<T>::operator-=(const Rational& rational)
{
    a = a * rational.b - b * rational.a;
    b = b * rational.b;
    return *this;
}

template <typename T>
inline Rational<T>& Rational<T>::operator*=(const Rational& rational)
{
    a *= rational.a;
    b *= rational.b;
    return *this;
}

template <typename T>
inline Rational<T>& Rational<T>::operator/=(const Rational& rational)
{
    a *= rational.b;
    b *= rational.a;
    return *this;
}

template <typename T>
Rational<T>& Rational<T>::add(const Rational& rational)
{
    T rationalA, rationalB, gcd;

    rationalA = rational.a;
    rationalB = rational.b;

    gcd = gcd2(b, rationalB);
    b /= gcd;
    a = a * (rationalB / gcd) + rationalA * b;
    gcd = gcd2(a, gcd);
    a /= gcd;
    b *= rationalB / gcd;

    return *this;
}

template <typename T>
Rational<T>& Rational<T>::sub(const Rational& rational)
{
    T rationalA, rationalB, gcd;

    rationalA = rational.a;
    rationalB = rational.b;

    gcd = gcd2(b, rationalB);
    b /= gcd;
    a = a * (rationalB / gcd) - rationalA * b;
    gcd = gcd2(a, gcd);
    a /= gcd;
    b *= rationalB / gcd;

    return *this;
}

template <typename T>
Rational<T>& Rational<T>::mul(const Rational& rational)
{
    T rationalA, rationalB, _gcd1, _gcd2;

    rationalA = rational.a;
    rationalB = rational.b;

    _gcd1 = gcd2(a, rationalB);
    _gcd2 = gcd2(rationalA, b);

    a = (a / _gcd1) * (rationalA / _gcd2);
    b = (b / _gcd2) * (rationalB / _gcd1);

    return *this;
}

template <typename T>
Rational<T>& Rational<T>::div(const Rational& rational)
{
    T rationalA, rationalB, _gcd1, _gcd2;

    rationalA = rational.a;
    rationalB = rational.b;

//        if (rationalA == T(0)) throw bad_rational();
    if (a == T(0)) return *this;

    _gcd1 = gcd2(a, rationalA);
    _gcd2 = gcd2(rationalB, b);

    a = (a / _gcd1) * (rationalB / _gcd2);
    b = (b / _gcd2) * (rationalA / _gcd1);

    if (b < T(0))
    {
        a = -a;
        b = -b;
    }

    return *this;
}

template <typename T>
inline Rational<T>& Rational<T>::operator+=(T n)
{
    a += n * b;
    return *this;
}

template <typename T>
inline Rational<T>& Rational<T>::operator-=(T n)
{
    a -= n * b;
    return *this;
}

template <typename T>
inline Rational<T>& Rational<T>::operator*=(T n)
{
    a *= n;
    return *this;
}

template <typename T>
inline Rational<T>& Rational<T>::operator/=(T n)
{
    b *= n;
    return *this;
}

template <typename T>
inline Rational<T>& Rational<T>::add(T n)
{
    add(CRational(n));
    return *this;
}

template <typename T>
inline Rational<T>& Rational<T>::sub(T n)
{
    sub(CRational(n));
    return *this;
}

template <typename T>
inline Rational<T>& Rational<T>::mul(T n)
{
    mul(CRational(n));
    return *this;
}

template <typename T>
inline Rational<T>& Rational<T>::div(T n)
{
    div(CRational(n));
    return *this;
}

template <typename T>
inline Rational<T> Rational<T>::operator+(const Rational& rational)
{
    return Rational(a * rational.b + b * rational.a, b * rational.b);
}

template <typename T>
inline Rational<T> Rational<T>::operator-(const Rational& rational)
{
    return Rational(a * rational.b - b * rational.a, b * rational.b);
}

template <typename T>
inline Rational<T> Rational<T>::operator*(const Rational& rational)
{
    return Rational(a * rational.a, b * rational.b);
}

template <typename T>
inline Rational<T> Rational<T>::operator/(const Rational& rational)
{
    return Rational(a * rational.b, b * rational.a);
}

template <typename T>
inline const Rational<T>& Rational<T>::operator++()
{
    a += b;
    return *this;
}

template <typename T>
inline const Rational<T>& Rational<T>::operator--()
{
    a -= b;
    return *this;
}

template <typename T>
inline bool Rational<T>::operator<(const Rational& rational) const
{
    if (b * rational.b > 0)
        return a * rational.b - b * rational.a > 0;
    return a * rational.b - b * rational.a < 0;
}

template <typename T>
inline bool Rational<T>::operator<=(const Rational& rational) const
{
    if (b * rational.b > 0)
        return a * rational.b - b * rational.a >= 0;
    return a * rational.b - b * rational.a <= 0;
}

template <typename T>
inline bool Rational<T>::operator>(const Rational& rational) const
{
    if (b * rational.b > 0)
        return a * rational.b - b * rational.a < 0;
    return a * rational.b - b * rational.a > 0;
}

template <typename T>
inline bool Rational<T>::operator>=(const Rational& rational) const
{
    if (b * rational.b > 0)
        return a * rational.b - b * rational.a <= 0;
    return a * rational.b - b * rational.a >= 0;
}

template <typename T>
inline bool Rational<T>::operator==(const Rational& rational) const
{
    T _gcd1, _gcd2, _a1, _b1, _a2, _b2;

    _gcd1 = gcd2(a, b);
    _gcd2 = gcd2(rational.a, rational.b);

    _a1 = a;
    _b1 = b;
    _a2 = rational.a;
    _b2 = rational.b;

    if (_gcd1 != T(1))
    {
        _a1 /= _gcd1;
        _b1 /= _gcd1;
    }

    if (_gcd2 != T(1))
    {
        _a2 /= _gcd2;
        _b2 /= _gcd2;
    }

    return (_a1 == _a2) && (_b1 == _b2);
}

template <typename T>
inline bool Rational<T>::operator<(T n) const
{
    return a < n * b;
}

template <typename T>
inline bool Rational<T>::operator<=(T n) const
{
    return a <= n * b;
}

template <typename T>
inline bool Rational<T>::operator>(T n) const
{
    return a > n * b;
}

template <typename T>
inline bool Rational<T>::operator>=(T n) const
{
    return a >= n * b;
}

template <typename T>
inline bool Rational<T>::operator==(T n) const
{
    return a == n * b;
}

template <typename T>
inline Rational<T> Rational<T>::float2rational(float f)
{
    Rt::s8 a, b;
    Rt::u4 rInt;
    Rt::s1 e;
    Rt::u4 m;
    Rt::s4 s;
    Rt::u1 ntzM;

    rInt = *((Rt::u4*)(&f));
    e = ((rInt & 0x7F800000) >> 23) - 127;
    m = (rInt & 0x7FFFFF) << 9; ntzM = Rt::ntz(m);
    s = ((rInt & 0x80000000) >> 31);

    b = 1 << (32 - ntzM);
    a = ~((Rt::s8)s - 1) ^ (b + (m >> ntzM)) + s;

    if (e)
    {
        if (e > 0) a <<= e;
        else b <<= -e;
    }

    return Rational<T>(T(a), T(b));
}

template <typename T>
inline void Rational<T>::normalize()
{
    T gcd = gcd1(T(a), T(b));
    a /= gcd;
    b /= gcd;
    if (b < T(0)) { a = -a; b = -b; }
}
