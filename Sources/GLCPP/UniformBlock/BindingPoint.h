#ifndef header_937E584A93AC
#define header_937E584A93AC

namespace GL
{
    namespace UniformBlock
    {
        class BindingPoint : public Rt::Object
        {
        private:
            GLuint binding;
            std::shared_ptr<Buffer> buffer;
            GLintptr offset;
            GLsizeiptr size;

        public:
            BindingPoint() {}
            BindingPoint(GLuint binding, std::shared_ptr<Buffer> buffer, GLintptr offset, GLsizeiptr size);
            BindingPoint(GLuint binding, GLsizeiptr size);
            virtual ~BindingPoint() {}

            GLuint getBinding() const;
            void setBinding(GLuint);

            std::shared_ptr<Buffer> getBuffer() const;
            void setBuffer(std::shared_ptr<Buffer>);

            GLintptr getOffset() const;
            void setOffset(GLintptr);

            GLsizeiptr getSize() const;
            void setSize(GLsizeiptr);

            void bind() const;
            static void unbind();

            Rt::u1* map(Buffer::Access access);
            static void unmap();
        };
    }
}

#endif
