#include <GLCPP/GL.h>

GL::Object::Object() : type(Type::none), needToDelete(false) {}

GL::Object::Object(Type type) : Object() {
    this->type = type;
}

GL::Object::~Object() {
    if (needToDelete) {
        switch (type) {
            case Type::Buffer: glDeleteBuffers(1, &ID); break;
            case Type::Framebuffer: glDeleteFramebuffers(1, &ID); break;
            case Type::Sampler: glDeleteSamplers(1, &ID); break;
            case Type::Shader: glDeleteShader(ID); break;
            case Type::ShaderProgram: glDeleteProgram(ID); break;
            case Type::VertexArray: glDeleteVertexArrays(1, &ID); break;
            case Type::Texture: glDeleteTextures(1, &ID); break;
            case Type::Query:
                #ifdef __APPLE__
                    #if TARGET_OS_IPHONE
                        #if __IPHONE_OS_VERSION_MAX_ALLOWED >= 50000
                        glDeleteQueriesEXT(1, &ID);
                        #endif
                    #elif TARGET_OS_MAC
                        glDeleteQueries(1, &ID);
                    #endif
                #elif defined(__linux)
                #elif defined(_WIN32)
                #elif defined(_WIN64)
                #endif
            break;
        }
    };
}

GLuint GL::Object::getID() const {
    return ID;
}

bool GL::Object::isValid() const {
    switch (type) {
        case Type::Buffer: return glIsBuffer(ID); break;
        case Type::Framebuffer: glIsFramebuffer(ID); break;
        case Type::Sampler: glIsSampler(ID); break;
        case Type::Shader: glIsShader(ID); break;
        case Type::ShaderProgram: glIsProgram(ID); break;
        case Type::VertexArray: glIsVertexArray(ID); break;
        case Type::Texture: glIsTexture(ID); break;
        case Type::Query: glIsQuery(ID); break;
    }
    return false;
}
