#include <GLCPP/GL.h>

GL::Query::Query() : enabled(false) {
    type = Object::Type::Query;
    #ifdef __APPLE__
        #if TARGET_OS_IPHONE
            glGenQueriesEXT(1, &ID);
        #elif TARGET_OS_MAC
            glGenQueries(1, &ID);
        #endif
    #elif defined(__linux)
    #elif defined(_WIN32)
    #elif defined(_WIN64)
    #endif
    if (!ID) Rt::error(0x4AE50602);
    needToDelete = true;
}

GL::Query::Query(bool enabled, GLenum target) : Query() {
    setEnabled(enabled);
    setTarget(target);
}

bool GL::Query::isEnabled() const {
    return enabled;
}

void GL::Query::setEnabled(bool enabled) {
    this->enabled = enabled;
}

GLenum GL::Query::getTarget() const {
    return target;
}

void GL::Query::setTarget(GLenum target) {
    this->target = target;
}

void GL::Query::begin() {
    if (enabled) {
        #ifdef __APPLE__
            #if TARGET_OS_IPHONE
                glBeginQueryEXT(target, ID);
            #elif TARGET_OS_MAC
                glBeginQuery(target, ID);
            #endif
        #elif defined(__linux)
        #elif defined(_WIN32)
        #elif defined(_WIN64)
        #endif
    }
}

void GL::Query::end() {
    if (enabled) {
        #ifdef __APPLE__
            #if TARGET_OS_IPHONE
                glEndQueryEXT(target);
            #elif TARGET_OS_MAC
                glEndQuery(target);
            #endif
        #elif defined(__linux)
        #elif defined(_WIN32)
        #elif defined(_WIN64)
        #endif
    }
}

void GL::Query::getResult(GLuint& result) const {
    #ifdef __APPLE__
        #if TARGET_OS_IPHONE
            glGetQueryObjectuivEXT(ID, GL_QUERY_RESULT_EXT, &result);
        #elif TARGET_OS_MAC
            glGetQueryObjectuiv(ID, GL_QUERY_RESULT, &result);
        #endif
    #elif defined(__linux)
    #elif defined(_WIN32)
    #elif defined(_WIN64)
    #endif
}

void GL::Query::getResult(GLint& result) const {
    #ifdef __APPLE__
        #if TARGET_OS_IPHONE
            glGetQueryObjectivEXT(ID, GL_QUERY_RESULT_EXT, &result);
        #elif TARGET_OS_MAC
            glGetQueryObjectiv(ID, GL_QUERY_RESULT, &result);
        #endif
    #elif defined(__linux)
    #elif defined(_WIN32)
    #elif defined(_WIN64)
    #endif
}
