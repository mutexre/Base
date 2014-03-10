#include <GLCPP/GL.h>

void GL::Framebuffer::bind(Target target, GLuint ID) {
    glBindFramebuffer(GLenum(target), ID);
}

GL::Framebuffer::Framebuffer() {
    type = Object::Type::Framebuffer;
    glGenFramebuffers(1, &ID);
    needToDelete = true;
}

void GL::Framebuffer::bind(Target target) {
    bind(target, ID);
}

void GL::Framebuffer::unbind(Target target) {
    bind(target, 0);
}
