#include <GLCPP/GL.h>

void GL::ShaderProgram::Attribute::set(const Rt::u1* ptr) const {
    switch (type) {
        case GL_FLOAT:
            glVertexAttrib1fv(location, (const GLfloat*)ptr);
        break;

        case GL_FLOAT_VEC2:
            glVertexAttrib2fv(location, (const GLfloat*)ptr);
        break;

        case GL_FLOAT_VEC3:
            glVertexAttrib3fv(location, (const GLfloat*)ptr);
        break;

        case GL_FLOAT_VEC4:
            glVertexAttrib4fv(location, (const GLfloat*)ptr);
        break;

        /*
        case GL_INT:
            glUniform1iv(location, size, (const GLint*)ptr);
        break;

        case GL_INT_VEC2:
            glUniform2iv(location, size, (const GLint*)ptr);
        break;

        case GL_INT_VEC3:
            glUniform3iv(location, size, (const GLint*)ptr);
        break;

        case GL_INT_VEC4:
            glUniform4iv(location, size, (const GLint*)ptr);
        break;

        case GL_UNSIGNED_INT:
            glUniform1uiv(location, size, (const GLuint*)ptr);
        break;

        case GL_UNSIGNED_INT_VEC2:
            glUniform2uiv(location, size, (const GLuint*)ptr);
        break;

        case GL_UNSIGNED_INT_VEC3:
            glUniform3uiv(location, size, (const GLuint*)ptr);
        break;

        case GL_UNSIGNED_INT_VEC4:
            glUniform4uiv(location, size, (const GLuint*)ptr);
        break;
        */
    }
}

/*
void GL::ShaderProgram::Attribute::set(const Rt::Value::Trait* value) const {
    switch (type) {
        case GL_FLOAT: {
            auto scalar = (const Rt::Value::Scalar<std::vector<float>>*)value;
            auto vec = scalar->get();
            glVertexAttrib1fv(location, vec.data());
        }
        break;

        case GL_FLOAT_VEC2: {
            auto scalar = (const Rt::Value::Scalar<std::vector<float>>*)value;
            auto vec = scalar->get();
            glVertexAttrib2fv(location, vec.data());
        }
        break;

        case GL_FLOAT_VEC3: {
            auto scalar = (const Rt::Value::Scalar<std::vector<float>>*)value;
            auto vec = scalar->get();
            glVertexAttrib3fv(location, vec.data());
        }
        break;

        case GL_FLOAT_VEC4: {
            auto scalar = (const Rt::Value::Scalar<std::array<float, 4>>*)value;
            auto vec = scalar->get();
            glVertexAttrib4fv(location, vec.data());
        }
        break;
    }
}
*/
