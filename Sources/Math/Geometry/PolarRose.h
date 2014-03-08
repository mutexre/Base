#ifndef header_7C7A7533A322
#define header_7C7A7533A322

namespace Math
{
    template <typename T = float, typename I = Rt::u4>
    struct PolarRose
    {
    private:
    /*
        Let
        x(phi) = r(phi) * cos(phi)
        y(phi) = r(phi) * sin(phi)

        By definition of period T:
            x(phi + T) = x(phi)
            y(phi + T) = y(phi)

        Consequently,
            cos((a/b) * phi + (a/b) * T) * cos(phi + T) = cos((a/b) * phi) * cos(phi)
            cos((a/b) * phi + (a/b) * T) * sin(phi + T) = cos((a/b) * phi) * sin(phi)

            (a/b) * T = pi * n1, T = pi * n2
            T = (b * n1 / a) * pi = n2 * pi
            
            n1 * b = n2 * a => n1 = a / GCD(a, b), n2 = b / GCD(a, b)

        Trere are two cases: 
            1. n1, n2 are even
            2. n1, n2 are odd
     
    */
        T calcAngularPeriod() {
            I GCD = gcd(ratio.a, ratio.b);
            I n1 = ratio.a / GCD;
            I n2 = ratio.b / GCD;
            if (n1 % 2 == 1 && n2 % 2 == 1) return n2 * T(M_PI);
            return T(2 * M_PI) * n2;
        }

    private:
        Rational<I> ratio;
        T angularPeriod;

    public:
        PolarRose() {}

        PolarRose(Rational<I> ratio) {
            setRatio(ratio);
        }

        PolarRose(I a, I b) {
            setRatio(a, b);
        }

        virtual ~PolarRose() {}

        Rational<I> getRatio() const {
            return ratio;
        }

        void setRatio(Rational<I> ratio) {
            this->ratio = ratio;
            angularPeriod = calcAngularPeriod();
        }

        void setRatio(I a, I b) {
            ratio.a = a;
            ratio.b = b;
            angularPeriod = calcAngularPeriod();
        }

        T getAngularPeriod() const {
            return angularPeriod;
        }

        std::vector<T> generateCoords(I n)
        {
            std::vector<T> coords(n << 1);

            T verticesCountInv = T(1) / T(n);
            for (I vertex = 0; vertex < n; vertex++) {
                T angle = angularPeriod * T(vertex) * verticesCountInv;
                T r = std::cos(ratio.template cast<T>() * angle);
                I offset = vertex << 1;
                coords[offset + 0] = r * std::cos(angle);
                coords[offset + 1] = r * std::sin(angle);
            }

            return coords;
        }
    };
}

#endif
