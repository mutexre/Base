#include <GLCPP/GL.h>

GL::UniformBlock::BindingPoint::BindingPoint(GLuint binding, std::shared_ptr<Buffer> buffer, GLintptr offset, GLsizeiptr size)
    : BindingPoint()
{
    this->binding = binding;
    this->buffer = buffer;
    this->offset = offset;
    this->size = size;
}

GL::UniformBlock::BindingPoint::BindingPoint(GLuint binding, GLsizeiptr size)
    : BindingPoint(binding, std::make_shared<Buffer>(), 0, size)
{
    GL::Buffer::bind(GL::Buffer::Target::Uniform, buffer.get());
    GL::Buffer::data(GL::Buffer::Target::Uniform, size, 0, GL_DYNAMIC_DRAW);
}

GLuint GL::UniformBlock::BindingPoint::getBinding() const {
    return binding;
}

void GL::UniformBlock::BindingPoint::setBinding(GLuint binding) {
    this->binding = binding;
}

std::shared_ptr<GL::Buffer>
GL::UniformBlock::BindingPoint::getBuffer() const {
    return buffer;
}

void GL::UniformBlock::BindingPoint::setBuffer(std::shared_ptr<Buffer> buffer) {
    this->buffer = buffer;
}

GLintptr GL::UniformBlock::BindingPoint::getOffset() const {
    return offset;
}

void GL::UniformBlock::BindingPoint::setOffset(GLintptr offset) {
    this->offset = offset;
}

GLsizeiptr GL::UniformBlock::BindingPoint::getSize() const {
    return size;
}

void GL::UniformBlock::BindingPoint::setSize(GLsizeiptr size) {
    this->size = size;
}

void GL::UniformBlock::BindingPoint::bind() const {
    Buffer::bindBufferRange(GL::Buffer::Target::Uniform, binding, offset, size, buffer.get());
}

void GL::UniformBlock::BindingPoint::unbind() {
    Buffer::unbind(GL::Buffer::Target::Uniform);
}

Rt::u1* GL::UniformBlock::BindingPoint::map(Buffer::Access access) {
    auto ptr = static_cast<Rt::u1*>(GL::Buffer::map(GL::Buffer::Target::Uniform, access));
    if (!ptr) Rt::error(0xD8ADD5CD);
    return ptr;
}

void GL::UniformBlock::BindingPoint::unmap() {
    GL::Buffer::unmap(GL::Buffer::Target::Uniform);
}
