#ifndef header_0B205E384DE2
#define header_0B205E384DE2

namespace GL
{
    namespace AUX
    {
        namespace Geometry
        {
            namespace Cube
            {
                struct Data
                {
                    static const GLfloat vertices[8][3];
                    static const GLuint d1[12][verticesPerEdge];
                    static const GLuint d2[6 * trianglesPerQuad][verticesPerTriangle];
                };
            };
        }
    }
}

#endif
