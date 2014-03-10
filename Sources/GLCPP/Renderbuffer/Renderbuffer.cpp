#include <GLCPP/GL.h>

GL::Renderbuffer::Renderbuffer() {
    type = Object::Type::Renderbuffer;
    glGenRenderbuffers(1, &ID);
    needToDelete = true;
}
