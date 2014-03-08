#ifndef header_7EF094D14AC5
#define header_7EF094D14AC5

namespace Color
{
    template <typename T = float>
    class HSVA : public HSV<T>
    {
    public:
        T a;

        HSVA() : HSV<T>() {}

        HSVA(T h, T s, T v, T a = T(1)) : HSV<T>(h, s, v) {
            this->a = a;
        }

        HSVA(const HSVA<T>& that) : HSV<T>(that) {
            a = that.a;
        }

        HSVA(const HSVA<T>* that) : HSV<T>(that) {
            a = that->a;
        }

        HSVA(const RGBA<T>& rgba) : HSV<T>(rgba) {
            *this = rgb2hsv(rgba);
            a = rgba.a;
        }
        
        HSVA(const RGBA<T>* rgba) : HSV<T>(rgba) {
            *this = rgb2hsv(rgba);
            a = rgba->a;
        }

        HSVA& operator=(const HSVA<T>& that) {
            this->h = that.h;
            this->s = that.s;
            this->v = that.v;
            this->a = that.a;
            return *this;
        }
        
        HSVA& operator=(const HSVA<T>* that) {
            this->h = that->h;
            this->s = that->s;
            this->v = that->v;
            this->a = that->a;
            return *this;
        }

        HSVA& operator=(const RGBA<T>& rgba) {
            *this = rgb2hsv(rgba);
            a = rgba.a;
            return *this;
        }
        
        HSVA& operator=(const RGBA<T>* rgba) {
            *this = rgb2hsv(rgba);
            a = rgba->a;
            return *this;
        }

        HSVA<T> operator*(T x) const {
            return HSVA<T>(this->h, this->s, this->v * x, a);
        }

        HSVA<T> operator-(const HSV<T>& that) const {
            return HSVA<T>(this->h - that.h, this->s, this->v, a);
        }

        HSVA<T> operator+(const HSV<T>& that) const {
            return HSVA<T>(this->h + that.h, this->s, this->v, a);
        }

        HSVA<T> operator-(const HSVA<T>& that) const {
            return HSVA<T>(this->h - that.h, this->s, this->v, a);
        }

        HSVA<T> operator+(const HSVA<T>& that) const {
            return HSVA<T>(this->h + that.h, this->s, this->v, a);
        }

        HSVA<T>& operator-=(const HSV<T>& that) {
            this->h -= that.h;
            return *this;
        }

        HSVA<T>& operator+=(const HSV<T>& that) {
            this->h += that.h;
            return *this;
        }

        HSVA<T>& operator-=(const HSVA<T>& that) {
            this->h -= that.h;
            return *this;
        }

        HSVA<T>& operator+=(const HSVA<T>& that) {
            this->h += that.h;
            return *this;
        }

        HSVA<T>& operator-=(float hue) {
            this->h -= hue;
            return *this;
        }

        HSVA<T>& operator+=(float hue) {
            this->h += hue;
            return *this;
        }
    };
}

#endif
