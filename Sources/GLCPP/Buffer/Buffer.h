#ifndef header_C212FB38665C
#define header_C212FB38665C

namespace GL
{
    class Buffer : public Object
    {
    public:
        enum class Target : GLenum {
            Array = GL_ARRAY_BUFFER,
            ElementArray = GL_ELEMENT_ARRAY_BUFFER,
            Uniform = GL_UNIFORM_BUFFER,
            TransformFeedback = GL_TRANSFORM_FEEDBACK_BUFFER,
            CopyRead = GL_COPY_READ_BUFFER,
            CopyWrite = GL_COPY_WRITE_BUFFER
        };

        enum class Access : GLenum {
            Read = GL_READ_ONLY,
            Write = GL_WRITE_ONLY,
            ReadWrite = GL_READ_WRITE
        };

    public:
        Buffer();
        virtual ~Buffer() {}

        static void bind(Target, GLuint ID);
        static void bind(Target, const Buffer&);
        static void bind(Target, const Buffer*);

        static void unbind(Target);
        static void unbind(Target, GLuint index);

        static void bindBufferRange(Target, GLuint index, GLintptr offset, GLsizeiptr size, GLuint ID);
        static void bindBufferRange(Target, GLuint index, GLintptr offset, GLsizeiptr size, const Buffer&);
        static void bindBufferRange(Target, GLuint index, GLintptr offset, GLsizeiptr size, const Buffer*);

        static void bindBufferBase(Target, GLuint index, GLuint ID);
        static void bindBufferBase(Target, GLuint index, const Buffer&);
        static void bindBufferBase(Target, GLuint index, const Buffer*);

        static GLint getCurrentBinding(Target);

        static void data(Target, GLsizeiptr size, const GLvoid* data, GLenum usage);
        static void subData(Target, GLintptr offset, GLsizeiptr size, const GLvoid* data);
        static void copySubData(Target readTarget, Target writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);

        static GLvoid* map(Target, Access);
        static void unmap(Target);

        void bind(Target);

        static GLint getSize(Target);
        static GLint getUsage(Target);
    };
}

#endif
