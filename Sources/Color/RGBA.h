#ifndef header_3FAC4C67F86C
#define header_3FAC4C67F86C

namespace Color
{
    template <typename T = float>
    class RGBA : public RGB<T>
    {
    public:
        T a;

        RGBA() : RGB<T>() {}

        RGBA(T r, T g, T b, T a = T(1)) : RGB<T>(r, g, b) {
            this->a = a;
        }

        RGBA(T x, T a = T(1)) : RGB<T>(x) {
            this->a = a;
        }

        RGBA(const RGB<T>& rgb, T a = T(1)) {
            this->r = rgb.r;
            this->g = rgb.g;
            this->b = rgb.b;
            this->a = a;
        }

        RGBA(const RGBA<T>& that) {
            this->r = that.r;
            this->g = that.g;
            this->b = that.b;
            a = that.a;
        }

        RGBA(const RGBA<T>* that) : RGB<T>(that->r, that->g, that->b), a(that->a) {}

        RGBA(const HSVA<T>& hsva) {
            *this = RGBA<T>(hsv2rgb(hsva), hsva.a);
        }
        
        RGBA(const HSVA<T>* hsva) {
            *this = hsv2rgb(hsva);
            a = hsva->a;
        }

        RGBA<T> operator+(const RGBA<T>& that) {
            return RGBA(this->r + that.r, this->g + that.g, this->b + that.b, a + that.a);
        }

        void set(T r, T g, T b, T a) {
            this->r = r;
            this->g = g;
            this->b = b;
            this->a = a;
        }

        RGBA<T> operator*(T x) const {
            return RGBA<T>(x * this->r, x * this->g, x * this->b, x * a);
        }

        RGBA<T> operator-(const RGBA<T>& that) const {
            return RGBA<T>(this->r - that.r, this->g - that.g, this->b - that.b, this->a - that.a);
        }
    };
}

#endif
