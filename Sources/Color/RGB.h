#ifndef header_CF489BAD
#define header_CF489BAD

#ifdef RGB
	#undef RGB
#endif

namespace Color
{
    template <typename T = float>
    class RGB : public Color
    {
    public:
        static RGB<T> gray(T x) {
            return RGB(x, x, x);
        };

        static RGB<T> black() {
            return gray(T(0));
        };

        static RGB<T> white() {
            return gray(T(1));
        };

    public:
        T r, g, b;

        RGB() {}

        RGB(T r, T g, T b) : RGB() {
            set(r, g, b);
        }

        RGB(T x) : RGB(x, x, x) {}

        RGB(const RGB<T>& that) : r(that.r), g(that.g), b(that.b) {}
        RGB(const RGB<T>* that) : r(that->r), g(that->g), b(that->b) {}

        RGB(const HSV<T>& hsv) {
            *this = hsv2rgb(hsv);
        }
        
        RGB(const HSV<T>* hsv) {
            *this = hsv2rgb(hsv);
        }

        RGB<T> operator+(const RGB<T>& that) {
            return RGB(r + that.r, g + that.g, b + that.b);
        }

        void set(T r, T g, T b) {
            this->r = r;
            this->g = g;
            this->b = b;
        }

        RGB<T> operator*(T x) const {
            return RGB<T>(x * r, x * g, x * b);
        }

        RGB<T> operator-(const RGB<T>& that) const {
            return RGB<T>(r - that.r, g - that.g, b - that.b);
        }
    };
}

#endif
