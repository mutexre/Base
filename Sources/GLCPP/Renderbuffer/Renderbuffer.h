#ifndef header_123EE395DCF4
#define header_123EE395DCF4

namespace GL
{
    class Renderbuffer : public GL::Object
    {
    private:
        GLenum target;

    public:
        Renderbuffer();
        virtual ~Renderbuffer() {}

        void attach(GLenum framebufferTarget, GLenum attachmentPoint, GLenum renderbufferTarget);
        void detach(GLenum framebufferTarget, GLenum attachmentPoint, GLenum renderbufferTarget);
    };
}

#endif
