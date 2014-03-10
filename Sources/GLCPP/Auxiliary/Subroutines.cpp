#include <fstream>
#include <sstream>
#include <GLCPP/GL.h>

/*
void GL::AUX::Subroutines::loadShaderProgram(ShaderSources& src,
                                             ShaderProgram* program,
                                             std::shared_ptr<VertexShader> vertexShader,
                                             std::shared_ptr<FragmentShader> fragmentShader)
{
    const char* programLog;

    try {
        vertexShader->init(GL::Shader::Type::Vertex, src.getVertex());
    }
    catch (...) {
        program->storeShaderLog(vertexShader.get());
        throw;
//        programLog = program->getLog();
//        if (programLog) Rt::error(0xBD09B98B, "%s\n", programLog);
    }

    try {
        fragmentShader->init(GL::Shader::Type::Fragment, src.getFragment());
    }
    catch (...) {
        program->storeShaderLog(fragmentShader.get());
        throw;
//        programLog = program->getLog();
//        if (programLog) Rt::error(0xFFCF521C, "%s\n", programLog);
    }

    program->init(vertexShader, fragmentShader);
//        programLog = program->getLog();
//        if (programLog) Rt::error(0x86B2BF3F, "%s\n", programLog);
}
*/