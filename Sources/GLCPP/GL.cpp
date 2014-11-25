#include <stdio.h>
#include <GLCPP/GL.h>

void GL::checkErrors()
{
    GLenum error = glGetError();
    switch (error) {
        case GL_NO_ERROR: RtLog("GL_NO_ERROR\n"); break;
        case GL_INVALID_ENUM: RtLog("GL_INVALID_ENUM\n"); break;
        case GL_INVALID_VALUE: RtLog("GL_INVALID_VALUE\n"); break;
        case GL_INVALID_OPERATION: RtLog("GL_INVALID_OPERATION\n"); break;
        case GL_OUT_OF_MEMORY: RtLog("GL_OUT_OF_MEMORY\n"); break;
        default: RtLog("OpenGL Error %u\n", error);
    };
}

void GL::printState(){
    printf("Bindings:\n  Vertex Array: %u\n  Array buffer: %u\n  Element Array buffer: %u\n",
           GL::VertexArray::getCurrentBinding(),
           GL::Buffer::getCurrentBinding(Buffer::Target::Array),
           GL::Buffer::getCurrentBinding(Buffer::Target::ElementArray));
}

GLsizeiptr GL::getSizeOfType(GLint type)
{
    switch (type) {
        case GL_HALF_FLOAT: return sizeof(GLhalf);

        case GL_FLOAT: return sizeof(GLfloat);
        case GL_FLOAT_VEC2: return 2 * sizeof(GLfloat);
        case GL_FLOAT_VEC3: return 3 * sizeof(GLfloat);
        case GL_FLOAT_VEC4: return 4 * sizeof(GLfloat);
        case GL_FLOAT_MAT2: return 2 * 2 * sizeof(GLfloat);
        case GL_FLOAT_MAT3: return 3 * 3 * sizeof(GLfloat);
        case GL_FLOAT_MAT4: return 4 * 4 * sizeof(GLfloat);
        case GL_FLOAT_MAT2x3: return 2 * 3 * sizeof(GLfloat);
        case GL_FLOAT_MAT2x4: return 2 * 4 * sizeof(GLfloat);
        case GL_FLOAT_MAT3x2: return 3 * 2 * sizeof(GLfloat);
        case GL_FLOAT_MAT3x4: return 3 * 4 * sizeof(GLfloat);
        case GL_FLOAT_MAT4x2: return 4 * 2 * sizeof(GLfloat);
        case GL_FLOAT_MAT4x3: return 4 * 3 * sizeof(GLfloat);

        case GL_BYTE: return sizeof(GLint);
        case GL_UNSIGNED_BYTE: return sizeof(GLuint);

        case GL_SHORT: return sizeof(GLshort);
        case GL_UNSIGNED_SHORT: return sizeof(GLushort);

        case GL_UNSIGNED_INT: return sizeof(GLuint);
        case GL_UNSIGNED_INT_VEC2: return 2 * sizeof(GLuint);
        case GL_UNSIGNED_INT_VEC3: return 3 * sizeof(GLuint);
        case GL_UNSIGNED_INT_VEC4: return 4 * sizeof(GLuint);

        case GL_INT: return sizeof(GLint);
        case GL_INT_VEC2: return 2 * sizeof(GLint);
        case GL_INT_VEC3: return 3 * sizeof(GLint);
        case GL_INT_VEC4: return 4 * sizeof(GLint);

        case GL_BOOL: return sizeof(GLboolean);
        case GL_BOOL_VEC2: return 2 * sizeof(GLboolean);
        case GL_BOOL_VEC3: return 3 * sizeof(GLboolean);
        case GL_BOOL_VEC4: return 4 * sizeof(GLboolean);

        case GL_DOUBLE: return sizeof(GLdouble);

        case GL_INT_2_10_10_10_REV: return 4;
        case GL_UNSIGNED_INT_2_10_10_10_REV: return 4;
    }
    Rt::error(0xE4675FA0);
}

void GL::printInfo() {
    printf("Vendor: %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version: %s\n", glGetString(GL_VERSION));
    printf("Extensions:\n");

    GLint extensionsCount;
    glGetIntegerv(GL_NUM_EXTENSIONS, &extensionsCount);
    for (auto i = 0; i < extensionsCount; i++)
        printf("  %s\n", glGetStringi(GL_EXTENSIONS, i));

    GLint maxGeometryOutputVertices;
    glGetIntegerv(GL_MAX_GEOMETRY_OUTPUT_VERTICES, &maxGeometryOutputVertices);
    printf("Max geometry output vertices: %u\n", maxGeometryOutputVertices);
/*
    GLint maxGeometryOutputVertices;
    glGetIntegerv(GL_MAX_GEOMETRY_OUTPUT_VERTICES, &maxGeometryOutputVertices);
    printf("Max geometry output vertices: %u\n", maxGeometryOutputVertices);
*/
}

void GL::printCurrentBindings() {
    printf("Vertex array: %u\nArray buffer: %u\nProgram: %u\n",
        GL::VertexArray::getCurrentBinding(),
        GL::Buffer::getCurrentBinding(GL::Buffer::Target::Array),
        GL::ShaderProgram::getCurrentProgram());
}
