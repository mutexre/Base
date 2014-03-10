#ifndef header_1238E40FF3F3
#define header_1238E40FF3F3

namespace GL
{
    class Viewport : public Rect<GLint>
    {
    public:
        Viewport() {};
        Viewport(Rect<GLint> rect) { set(rect); }
        Viewport(GLint x, GLint y, GLint w, GLint h) { set(x, y, w, h); }

        virtual void set(Rect<GLint> rect) { x = rect.x; y = rect.y; w = rect.w; h = rect.h; }
        virtual void set(GLint x, GLint y, GLint w, GLint h) { this->x = x; this->y = y; this->w = w; this->h = h; }

        virtual void install() { glViewport(x, y, w, h); }

        virtual float getAspectRatio() {
            return float(w) / float(h);
        }
    };
}

#endif
