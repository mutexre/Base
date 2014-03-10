#ifndef header_443392EBDB36
#define header_443392EBDB36

namespace GL
{
    class Framebuffer : public Object
    {
    public:
        enum class Target : GLenum {
            FB = GL_FRAMEBUFFER,
            Read = GL_READ_FRAMEBUFFER,
            Draw = GL_DRAW_FRAMEBUFFER,
        };

    private:
        static void bind(Target, GLuint ID);

    public:
        Framebuffer();
        virtual ~Framebuffer() {}

        void bind(Target);
        void unbind(Target);
    };
}

#endif
