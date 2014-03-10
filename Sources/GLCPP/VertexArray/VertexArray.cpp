#include <GLCPP/GL.h>


#if defined __APPLE__ && TARGET_OS_IPHONE

void GL::VertexArray::bind(GLuint ID) {
    glBindVertexArrayOES(ID);
}

#else

void GL::VertexArray::bind(GLuint ID) {
    glBindVertexArray(ID);
}

#endif

void GL::VertexArray::bind(const VertexArray& vertexArray) {
    bind(vertexArray.getID());
}

void GL::VertexArray::bind(const VertexArray* vertexArray) {
    bind(vertexArray->getID());
}

void GL::VertexArray::unbind() {
    bind(GLuint(0));
}

void GL::VertexArray::bind() {
    bind(ID);
}

GLint GL::VertexArray::getCurrentBinding() {
    GLint binding;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &binding);
    return binding;
}

GL::VertexArray::VertexArray() {
    type = Object::Type::VertexArray;
#if defined __APPLE__ && TARGET_OS_IPHONE
    glGenVertexArraysOES(1, &ID);
#else
    glGenVertexArrays(1, &ID);
#endif
    needToDelete = true;
}

void GL::VertexArray::enableAttribArray(GLuint index, bool enable)
{
    if (enable)
        glEnableVertexAttribArray(index);
    else
        glDisableVertexAttribArray(index);
}

void GL::VertexArray::enableAttribArray(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLsizeiptr offset) {
    AttribPointer(size, type, normalized, stride, offset).set(index);
    enableAttribArray(index, true);
}

void GL::VertexArray::set(GLuint attrIndex, bool enable, std::shared_ptr<GL::Buffer> buffer, AttribPointer ptr) {
    Buffer::bind(Buffer::Target::Array, buffer.get());
    ptr.set(attrIndex);
    enableAttribArray(attrIndex, enable);
    attrs.insert(std::make_pair(attrIndex, std::make_tuple(enable, buffer, ptr)));
}

void GL::VertexArray::setElementArray(std::shared_ptr<GL::Buffer> buffer) {
    Buffer::bind(Buffer::Target::ElementArray, buffer.get());
    elementArrayBuffer = buffer;
}

const GL::VertexArray::Attributes&
GL::VertexArray::getAttributes() const {
    return attrs;
}
