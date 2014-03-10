#include <GLCPP/GL.h>

void GL::PixelStore::get(GLenum param, GLint& value) {
    glGetIntegerv(param, &value);
}

void GL::PixelStore::get(GLenum param, GLfloat& value) {
    glGetFloatv(param, &value);
}

void GL::PixelStore::set(GLenum param, GLint value) {
    glPixelStorei(param, value);
}

void GL::PixelStore::set(GLenum param, GLfloat value) {
    glPixelStoref(param, value);
}

void GL::PixelStore::get(Parameter::Pack param, GLint& value) {
    get(GLenum(param), value);
}

void GL::PixelStore::get(Parameter::Pack param, GLfloat& value) {
    get(GLenum(param), value);
}

void GL::PixelStore::get(Parameter::Unpack param, GLint& value) {
    get(GLenum(param), value);
}

void GL::PixelStore::get(Parameter::Unpack param, GLfloat& value) {
    get(GLenum(param), value);
}

void GL::PixelStore::set(Parameter::Pack param, GLint value) {
    set(GLenum(param), value);
}

void GL::PixelStore::set(Parameter::Pack param, GLfloat value) {
    set(GLenum(param), value);
}

void GL::PixelStore::set(Parameter::Unpack param, GLint value) {
    set(GLenum(param), value);
}

void GL::PixelStore::set(Parameter::Unpack param, GLfloat value) {
    set(GLenum(param), value);
}
