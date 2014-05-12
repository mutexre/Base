#ifndef header_a71f384ebebe
#define header_a71f384ebebe

namespace SG
{
    class DrawCall
    {
    public:
        enum class Kind {
            arrays,
            elements
        };

    public:
        Kind kind;

        union {
            struct {
                GLenum mode;
                GLint first;
                GLsizei count;
            }
            arrays;

            struct {
                GLenum mode;
                GLsizei count;
                GLenum type;
                GLsizeiptr indicesOffsetInBytes;
                GLsizei numberOfInstances;
                GLint baseVertex;
            }
            elements;
        };

    public:
        DrawCall() {}

        DrawCall(GLenum mode, GLint first, GLsizei count) {
            init(mode, first, count);
        }

        DrawCall(GLenum mode, GLsizei count, GLenum type, GLsizeiptr indicesOffsetInBytes, GLsizei numberOfInstances = 1, GLint baseVertex = 0) {
            init(mode, count, type, indicesOffsetInBytes, numberOfInstances, baseVertex);
        }

        virtual ~DrawCall() {}

        void init(GLenum mode, GLint first, GLsizei count) {
            kind = Kind::arrays;
            arrays.mode = mode;
            arrays.first = first;
            arrays.count = count;
        }

        void init(GLenum mode, GLsizei count, GLenum type, GLsizeiptr indicesOffsetInBytes, GLsizei numberOfInstances = 1, GLint baseVertex = 0) {
            kind = Kind::elements;
            elements.mode = mode;
            elements.count = count;
            elements.type = type;
            elements.indicesOffsetInBytes = indicesOffsetInBytes;
            elements.numberOfInstances = numberOfInstances;
            elements.baseVertex = baseVertex;
        }

        virtual void operator()() {
            switch (kind) {
                case Kind::arrays:
                    glDrawArrays(arrays.mode, arrays.first, arrays.count);
                break;

                case Kind::elements:
                #if defined __APPLE__ && TARGET_OS_IPHONE
                    glDrawElements(elements.mode,
                                    elements.count,
                                    elements.type,
                                    ((const GLchar*)0) + elements.indicesOffsetInBytes);
                #else
                    if (elements.baseVertex > 0) {
                        if (elements.numberOfInstances > 1)
                            glDrawElementsInstancedBaseVertex(elements.mode,
                                                              elements.count,
                                                              elements.type,
                                                              ((const GLchar*)0) + elements.indicesOffsetInBytes,
                                                              elements.numberOfInstances,
                                                              elements.baseVertex);
                        else
                            glDrawElementsBaseVertex(elements.mode,
                                                     elements.count,
                                                     elements.type,
                                                     ((const GLchar*)0) + elements.indicesOffsetInBytes,
                                                     elements.baseVertex);
                    }
                    else {
                        if (elements.numberOfInstances > 1)
                            glDrawElementsInstanced(elements.mode,
                                                    elements.count,
                                                    elements.type,
                                                    ((const GLchar*)0) + elements.indicesOffsetInBytes,
                                                    elements.numberOfInstances);
                        else
                            glDrawElements(elements.mode,
                                           elements.count,
                                           elements.type,
                                           ((const GLchar*)0) + elements.indicesOffsetInBytes);
                    }
                #endif
                break;
            }
        }
    };
}

#endif
