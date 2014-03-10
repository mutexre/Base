#ifndef header_D182BE4899C7
#define header_D182BE4899C7

namespace GL
{
    template<typename T>
    struct Rect
    {
    public:
        T x, y, w, h;

        Rect() : x(0), y(0), w(0), h(0) {}

        Rect(T x, T y, T w, T h) {
            this->x = x;
            this->y = y;
            this->w = w;
            this->h = h;
        }
    };
}

#endif
