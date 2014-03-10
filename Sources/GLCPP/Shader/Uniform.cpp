#include <GLCPP/GL.h>

GLsizeiptr GL::ShaderProgram::Uniform::calcSize() const
{
    if (matrixStride <= 0) {
        if (arrayStride <= 0) return getSizeOfType(type);
        return size * arrayStride;
    }

    return size * matrixStride;
}

void GL::ShaderProgram::Uniform::set(const Rt::u1* ptr, GLboolean transpose) const {
    switch (type) {
        case GL_FLOAT:
            glUniform1fv(location, size, (const GLfloat*)ptr);
        break;

        case GL_FLOAT_VEC2:
            glUniform2fv(location, size, (const GLfloat*)ptr);
        break;

        case GL_FLOAT_VEC3:
            glUniform3fv(location, size, (const GLfloat*)ptr);
        break;

        case GL_FLOAT_VEC4:
            glUniform4fv(location, size, (const GLfloat*)ptr);
        break;

        case GL_FLOAT_MAT2:
            glUniformMatrix2fv(location, size, transpose, (const GLfloat*)ptr);
        break;

        case GL_FLOAT_MAT3:
            glUniformMatrix3fv(location, size, transpose, (const GLfloat*)ptr);
        break;

        case GL_FLOAT_MAT4:
            glUniformMatrix4fv(location, size, transpose, (const GLfloat*)ptr);
        break;

        case GL_FLOAT_MAT2x3:
            glUniformMatrix2x3fv(location, size, transpose, (const GLfloat*)ptr);
        break;

        case GL_FLOAT_MAT2x4:
            glUniformMatrix2x4fv(location, size, transpose, (const GLfloat*)ptr);
        break;

        case GL_FLOAT_MAT3x2:
            glUniformMatrix3x2fv(location, size, transpose, (const GLfloat*)ptr);
        break;

        case GL_FLOAT_MAT3x4:
            glUniformMatrix3x4fv(location, size, transpose, (const GLfloat*)ptr);
        break;

        case GL_FLOAT_MAT4x2:
            glUniformMatrix4x2fv(location, size, transpose, (const GLfloat*)ptr);
        break;

        case GL_FLOAT_MAT4x3:
            glUniformMatrix4x3fv(location, size, transpose, (const GLfloat*)ptr);
        break;

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

        case GL_BOOL:
        case GL_BOOL_VEC2:
        case GL_BOOL_VEC3:
        case GL_BOOL_VEC4:;
    }
}

/*
void GL::ShaderProgram::Uniform::set(const Rt::Value::Trait* value, GLboolean transpose) const {
    switch (type) {
        case GL_FLOAT: {
            auto scalar = dynamic_cast<const Rt::Value::Scalar<std::vector<float>>*>(value);
            if (scalar) {
                auto& vec = scalar->get();
                glUniform1fv(location, vec.size(), vec.data());
            }
            else
                Rt::error(0x45FE8676);
        }
        break;

        case GL_FLOAT_VEC2: {
            auto scalar = (const Rt::Value::Scalar<std::vector<float>>*)value;
            auto vec = scalar->get();
            glUniform2fv(location, vec.size() >> 1, vec.data());
        }
        break;

        case GL_FLOAT_VEC3: {
            auto scalar = (const Rt::Value::Scalar<std::vector<float>>*)value;
            auto vec = scalar->get();
            glUniform3fv(location, vec.size() / 3, vec.data());
        }
        break;

        case GL_FLOAT_VEC4: {
            auto scalar = (const Rt::Value::Scalar<std::vector<float>>*)value;
            auto& vec = scalar->get();
            glUniform4fv(location, vec.size() >> 2, vec.data());
        }
        break;

        case GL_FLOAT_MAT2: {
            auto scalar = (const Rt::Value::Scalar<std::vector<float>>*)value;
            auto& vec = scalar->get();
            glUniformMatrix2fv(location, vec.size() >> 2, transpose, vec.data());
        }
        break;

        case GL_FLOAT_MAT3: {
            auto scalar = (const Rt::Value::Scalar<std::vector<float>>*)value;
            auto& vec = scalar->get();
            glUniformMatrix3fv(location, vec.size() / 9, transpose, vec.data());
        }
        break;

        case GL_FLOAT_MAT4: {
            auto scalar = (const Rt::Value::Scalar<std::vector<float>>*)value;
            auto& vec = scalar->get();
            glUniformMatrix4fv(location, vec.size() >> 4, transpose, vec.data());
        }
        break;

        case GL_FLOAT_MAT2x3:
            glUniformMatrix2x3fv(location, size, transpose, (const GLfloat*)ptr);
        break;

        case GL_FLOAT_MAT2x4:
            glUniformMatrix2x4fv(location, size, transpose, (const GLfloat*)ptr);
        break;

        case GL_FLOAT_MAT3x2:
            glUniformMatrix3x2fv(location, size, transpose, (const GLfloat*)ptr);
        break;

        case GL_FLOAT_MAT3x4:
            glUniformMatrix3x4fv(location, size, transpose, (const GLfloat*)ptr);
        break;

        case GL_FLOAT_MAT4x2:
            glUniformMatrix4x2fv(location, size, transpose, (const GLfloat*)ptr);
        break;

        case GL_FLOAT_MAT4x3:
            glUniformMatrix4x3fv(location, size, transpose, (const GLfloat*)ptr);
        break;

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

    }
}
*/
