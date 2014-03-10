#include <GLCPP/GL.h>

void GL::Buffer::bind(Target target, GLuint ID) {
    glBindBuffer(GLenum(target), ID);
}

void GL::Buffer::bindBufferRange(Target target, GLuint index, GLintptr offset, GLsizeiptr size, GLuint ID) {
    glBindBufferRange(GLenum(target), index, ID, offset, size);
}

void GL::Buffer::bindBufferBase(Target target, GLuint index, GLuint ID) {
    glBindBufferBase(GLenum(target), index, ID);
}

void GL::Buffer::bind(Target target, const Buffer& buffer) {
    bind(target, buffer.getID());
}

void GL::Buffer::bind(Target target, const Buffer* buffer) {
    bind(target, buffer->getID());
}

void GL::Buffer::unbind(Target target) {
    bind(target, GLuint(0));
}

void GL::Buffer::unbind(Target target, GLuint index) {
    bindBufferBase(target, index, GLuint(0));
}

void GL::Buffer::bindBufferRange(Target target, GLuint index, GLintptr offset, GLsizeiptr size, const Buffer& buffer) {
    bindBufferRange(target, index, offset, size, buffer.getID());
}

void GL::Buffer::bindBufferRange(Target target, GLuint index, GLintptr offset, GLsizeiptr size, const Buffer* buffer) {
    bindBufferRange(target, index, offset, size, buffer->getID());
}

void GL::Buffer::bindBufferBase(Target target, GLuint index, const Buffer& buffer) {
    bindBufferBase(target, index, buffer.getID());
}

void GL::Buffer::bindBufferBase(Target target, GLuint index, const Buffer* buffer) {
    bindBufferBase(target, index, buffer->getID());
}

GLint GL::Buffer::getCurrentBinding(Target target) {
    GLint binding;
    GLenum pname;

    switch (target) {
        case Target::Array: pname = GL_ARRAY_BUFFER_BINDING; break;
        case Target::ElementArray: pname = GL_ELEMENT_ARRAY_BUFFER_BINDING; break;
        default: Rt::error(0x7DC4872D);
    }

    glGetIntegerv(pname, &binding);

    return binding;
}

GL::Buffer::Buffer() {
    type = Object::Type::Buffer;
    glGenBuffers(1, &ID);
    needToDelete = true;
}

void GL::Buffer::data(Target target, GLsizeiptr size, const GLvoid* data, GLenum usage) {
    glBufferData(GLenum(target), size, data, usage);
}

void GL::Buffer::subData(Target target, GLintptr offset, GLsizeiptr size, const GLvoid* data) {
    glBufferSubData(GLenum(target), offset, size, data);
}

void GL::Buffer::copySubData(Target readTarget, Target writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size) {
    glCopyBufferSubData(GLenum(readTarget), GLenum(writeTarget), readOffset, writeOffset, size);
}

#if defined __APPLE__ && TARGET_OS_IPHONE

GLvoid* GL::Buffer::map(Target target, GLenum access) {
    return glMapBufferOES(target, access);
}

void GL::Buffer::unmap(Target target) {
    glUnmapBufferOES(target);
}

#else

GLvoid* GL::Buffer::map(Target target, Access access) {
    return glMapBuffer(GLenum(target), GLenum(access));
}

void GL::Buffer::unmap(Target target) {
    if (glUnmapBuffer(GLenum(target)) != GL_TRUE)
        Rt::error(0x3480E668);
}

#endif

void GL::Buffer::bind(Target target) {
    bind(target, ID);
}

GLint GL::Buffer::getSize(Target target) {
    GLint retval;
    glGetBufferParameteriv(GLenum(target), GL_BUFFER_SIZE, &retval);
    return retval;
}

GLint GL::Buffer::getUsage(Target target) {
    GLint retval;
    glGetBufferParameteriv(GLenum(target), GL_BUFFER_USAGE, &retval);
    return retval;
}
