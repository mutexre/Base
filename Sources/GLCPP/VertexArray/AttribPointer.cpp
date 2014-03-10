#include <GLCPP/GL.h>

GL::VertexArray::AttribPointer::AttribPointer() {}

GL::VertexArray::AttribPointer::AttribPointer(GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLsizeiptr offset) {
    this->size = size;
    this->type = type;
    this->normalized = normalized;
    this->stride = stride;
    this->offset = offset;
}

GL::VertexArray::AttribPointer::AttribPointer(GLint size, GLenum type, GLboolean normalized, Rt::StrideOffset<Rt::u4> strideAndOffset) :
    AttribPointer(size, type, normalized, strideAndOffset.stride, strideAndOffset.offset)
{}

GL::VertexArray::AttribPointer::AttribPointer(GLint size, GLenum type, GLboolean normalized, std::pair<Rt::u4, Rt::u4> strideAndOffset) :
    AttribPointer(size, type, normalized, strideAndOffset.first, strideAndOffset.second)
{}

void GL::VertexArray::AttribPointer::set(GLuint index, GLsizeiptr offset) {
    glVertexAttribPointer(index, size, type, normalized, stride, (GLvoid*)(((Rt::u1*)0) + offset + this->offset));
}
