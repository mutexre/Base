#include <GLCPP/GL.h>

const GLfloat GL::AUX::Geometry::Cube::Data::vertices[8][3] =
    {{ -1.0f, -1.0f, -1.0f },
     { -1.0f, -1.0f, +1.0f },
     { -1.0f, +1.0f, -1.0f },
     { -1.0f, +1.0f, +1.0f },
     { +1.0f, -1.0f, -1.0f },
     { +1.0f, -1.0f, +1.0f },
     { +1.0f, +1.0f, -1.0f },
     { +1.0f, +1.0f, +1.0f }};

const GLuint GL::AUX::Geometry::Cube::Data::edges[12][verticesPerEdge] =
    {{ 0, 4 },
     { 1, 5 },
     { 2, 6 },
     { 3, 7 },
     { 0, 2 },
     { 1, 3 },
     { 4, 6 },
     { 5, 7 },
     { 0, 1 },
     { 2, 3 },
     { 4, 5 },
     { 6, 7 }};

const GLuint GL::AUX::Geometry::Cube::Data::triangles[6 * trianglesPerQuad][verticesPerTriangle] =
    {{ 0, 1, 3 }, { 3, 2, 0 },
     { 5, 4, 6 }, { 6, 7, 5 },
     { 0, 1, 5 }, { 5, 4, 0 },
     { 3, 2, 6 }, { 6, 7, 3 },
     { 0, 2, 6 }, { 6, 4, 0 },
     { 3, 1, 5 }, { 5, 7, 3 }};
