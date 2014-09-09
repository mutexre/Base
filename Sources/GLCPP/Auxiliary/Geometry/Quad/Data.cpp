#include <GLCPP/GL.h>

const GLfloat GL::AUX::Geometry::Quad::Data::vertices[4][2] =
    {{ -1.0f, -1.0f },
     { -1.0f, +1.0f },
     { +1.0f, -1.0f },
     { +1.0f, +1.0f }};

const GLuint GL::AUX::Geometry::Quad::Data::d1[4][2] =
    {{ 0, 1 },
     { 2, 3 },
     { 0, 2 },
     { 1, 3 }};

const GLuint GL::AUX::Geometry::Quad::Data::d2[2][3] = {{ 0, 1, 2 }, { 3, 2, 1 }};
