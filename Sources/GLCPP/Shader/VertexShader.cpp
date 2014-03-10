#include <GLCPP/GL.h>

GL::VertexShader::VertexShader(std::string source) : GL::Shader(Type::Vertex, source) {}
