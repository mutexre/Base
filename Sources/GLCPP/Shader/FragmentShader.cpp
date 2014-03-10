#include <GLCPP/GL.h>

GL::FragmentShader::FragmentShader(std::string source) : GL::Shader(GL::Shader::Type::Fragment, source) {}
