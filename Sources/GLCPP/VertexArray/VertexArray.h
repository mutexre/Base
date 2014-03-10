#ifndef header_80D9BB4D2F29
#define header_80D9BB4D2F29

namespace GL
{
    class VertexArray : public Object
    {
    public:
        struct AttribPointer {
            GLint size;
            GLenum type;
            GLboolean normalized;
            GLsizei stride;
            GLsizeiptr offset;

            AttribPointer();
            AttribPointer(GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLsizeiptr offset);
            AttribPointer(GLint size, GLenum type, GLboolean normalized, Rt::StrideOffset<Rt::u4> strideAndOffset);
            AttribPointer(GLint size, GLenum type, GLboolean normalized, std::pair<Rt::u4, Rt::u4> strideAndOffset);
            void init(GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLsizeiptr offset);
            void set(GLuint index, GLsizeiptr offset = 0);
        };

        typedef std::map<GLuint, std::tuple<bool, std::shared_ptr<GL::Buffer>, AttribPointer>> Attributes;

    private:
        Attributes attrs;
        std::shared_ptr<GL::Buffer> elementArrayBuffer;

    private:
        static void bind(GLuint ID);
        void setBuffer(GLenum target, Buffer* buffer, Buffer*& currentBuffer);

    public:
        VertexArray();
        virtual ~VertexArray() {}

        virtual void set(GLuint attrIndex, bool enable, std::shared_ptr<GL::Buffer>, AttribPointer);
        virtual void setElementArray(std::shared_ptr<GL::Buffer>);

        static void bind(const VertexArray& vertexArray);
        static void bind(const VertexArray* vertexArray);
        static void unbind();

        void bind();

        static GLint getCurrentBinding();

        static void bindArrayBuffer(std::shared_ptr<GL::Buffer>);
        static void bindElementArrayBuffer(std::shared_ptr<GL::Buffer>);

        static void enableAttribArray(GLuint index, bool = true);
        static void enableAttribArray(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLsizeiptr offset);

        const Attributes& getAttributes() const;
    };
}

#endif
