#ifndef header_07EF8FE3A2BB
#define header_07EF8FE3A2BB

namespace GL
{
    class Object : public Rt::Object
    {
    public:
        enum class Type {
            none,
            Shader,
            ShaderProgram,
            Buffer,
            VertexArray,
            Framebuffer,
            Renderbuffer,
            Texture,
            Sampler,
            Query
        };

    protected:
        Type type;
        GLuint ID;
        bool needToDelete;

    public:
        Object();
        Object(Type);
        virtual ~Object();

        GLuint getID() const;
        bool isValid() const;
    };
}

#endif
