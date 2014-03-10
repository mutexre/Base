#include <GLCPP/GL.h>

GL::GeometryShader::GeometryShader(std::string source) : GL::Shader(Type::Geometry, source) {}
