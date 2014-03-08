#ifndef header_ECD04562
#define header_ECD04562

namespace Color
{
    template <typename T = float>
    class HSV : public Color
    {
    public:
        T h, s, v;

        HSV() {}

        HSV(T h, T s, T v) : HSV() {
            this->h = h;
            this->s = s;
            this->v = v;
        }

        HSV(const HSV<T>& that) : HSV() {
            h = that.h;
            s = that.s;
            v = that.v;
        }

        HSV(const HSV<T>* that) : HSV() {
            h = that->h;
            s = that->s;
            v = that->v;
        }

        HSV(const RGB<T>& rgb) : HSV() {
            *this = rgb2hsv(rgb);
        }
        
        HSV(const RGB<T>* rgb) : HSV() {
            *this = rgb2hsv(rgb);
        }

        HSV& operator=(const HSV<T>& that) {
            h = that.h;
            s = that.s;
            v = that.v;
            return *this;
        }
        
        HSV& operator=(const HSV<T>* that) {
            h = that->h;
            s = that->s;
            v = that->v;
            return *this;
        }

        HSV& operator=(const RGB<T>& rgb) {
            *this = rgb2hsv(rgb);
            return *this;
        }
        
        HSV& operator=(const RGB<T>* rgb) {
            *this = rgb2hsv(rgb);
            return *this;
        }

        HSV<T> operator*(T x) const {
            return HSV<T>(h, s, v * x);
        }

        HSV<T> operator-(const HSV<T>& that) const {
            return HSV<T>(h - that.h, s - that.s, v - that.v);
        }

        HSV<T> operator+(const HSV<T>& that) const {
            return HSV<T>(h + that.h, s + that.s, v + that.v);
        }
    };
}

#endif
