#include <GLCPP/GL.h>

GL::Shader::Shader(Type shaderType) {
    type = Object::Type::Shader;

    ID = glCreateShader(GLenum(shaderType));
    if (!ID) Rt::error(0x2A334055);

    needToDelete = true;
}

GL::Shader::Shader(Type type, std::string source) : Shader(type) {
    GLint isCompiled;
    const GLchar* sources[] = { source.c_str() };

    glShaderSource(ID, 1, sources, 0);
    glCompileShader(ID);
    glGetShaderiv(ID, GL_COMPILE_STATUS, &isCompiled);

    if (!isCompiled) {
        GLsizei logLength;

        glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &logLength);
        if (logLength > 0) {
            GLsizei actualCompilationLogLength;

            auto log = new GLchar[logLength + 1];
            memset(log, 0, logLength + 1);

            glGetShaderInfoLog(ID, logLength, &actualCompilationLogLength, log);

            throw CompileError(log);
        }

        throw CompileError();
    }
}
