#include <GLCPP/GL.h>

GL::VertexArrayKit::VertexArrayKit(Options d0,
                                   Options d1,
                                   Options d2)
{
    setPointsOptions(d0);
    setLinesOptions(d1);
    setTrianglesOptions(d2);
}

void GL::VertexArrayKit::render()
{
#if defined __APPLE__ && TARGET_OS_IPHONE
    if (d1.enabled) {
        d1.bind();
        glDrawElements(GL_LINES,
                       verticesPerTriangle * d1.count,
                       d1.type,
                       (const GLchar*)d1.offset);
    }

    if (d2.enabled) {
        d2.bind();
        glDrawElements(GL_TRIANGLES,
                       verticesPerTriangle * d2.count,
                       d2.type,
                       (const GLchar*)d2.offset);
    }
#else
        if (d2.enabled)
        {
            d2.bind();
            if (d2.baseVertex > 0) {
                if (d2.numberOfInstances > 1)
                    glDrawElementsInstancedBaseVertex(GL_TRIANGLES,
                                                      verticesPerTriangle * d2.count,
                                                      d2.type,
                                                      (const GLchar*)d2.offset,
                                                      d2.numberOfInstances,
                                                      d2.baseVertex);
                else
                    glDrawElementsBaseVertex(GL_TRIANGLES,
                                             verticesPerTriangle * d2.count,
                                             d2.type,
                                             (const GLchar*)d2.offset,
                                             d2.baseVertex);
            }
            else {
                if (d2.numberOfInstances > 1)
                    glDrawElementsInstanced(GL_TRIANGLES,
                                            GL::verticesPerTriangle * d2.count,
                                            d2.type,
                                            (const GLchar*)d2.offset,
                                            d2.numberOfInstances);
                else
                    glDrawElements(GL_TRIANGLES,
                                   GL::verticesPerTriangle * d2.count,
                                   d2.type,
                                   (const GLchar*)d2.offset);
            }
        }

        if (d1.enabled)
        {
            d1.bind();
            if (d1.baseVertex > 0)
            {
                if (d1.numberOfInstances > 1)
                    glDrawElementsInstancedBaseVertex(GL_LINES,
                                                      GL::verticesPerEdge * d1.count,
                                                      d1.type,
                                                      (const GLchar*)d1.offset,
                                                      d1.numberOfInstances,
                                                      d1.baseVertex);
                else
                    glDrawElementsBaseVertex(GL_LINES,
                                             GL::verticesPerEdge * d1.count,
                                             d1.type,
                                             (const GLchar*)d1.offset,
                                             d1.baseVertex);
            }
            else {
                if (d1.numberOfInstances > 1)
                    glDrawElementsInstanced(GL_LINES,
                                            GL::verticesPerEdge * d1.count,
                                            d1.type,
                                            (const GLchar*)d1.offset,
                                            d1.numberOfInstances);
                else
                    glDrawElements(GL_LINES,
                                   GL::verticesPerEdge * d1.count,
                                   d1.type,
                                   (const GLchar*)d1.offset);
            }
        }
#endif

    if (d0.enabled) {
        d0.bind();
        glDrawArrays(GL_POINTS, d0.offset, d0.count);
    }
}

GL::VertexArrayKit::Options GL::VertexArrayKit::getPointsOptions() const {
    return d0;
}

void GL::VertexArrayKit::setPointsOptions(Options options) {
    d0 = options;
}

void GL::VertexArrayKit::setPointsShaderProgram(std::shared_ptr<ShaderProgram> program) {
    d0.program = program;
}

GL::VertexArrayKit::Options GL::VertexArrayKit::getLinesOptions() const {
    return d1;
}

void GL::VertexArrayKit::setLinesOptions(Options options) {
    d1 = options;
}

void GL::VertexArrayKit::setLinesShaderProgram(std::shared_ptr<ShaderProgram> program) {
    d1.program = program;
}

GL::VertexArrayKit::Options GL::VertexArrayKit::getTrianglesOptions() const {
    return d2;
}

void GL::VertexArrayKit::setTrianglesOptions(Options options) {
    d2 = options;
}

void GL::VertexArrayKit::setTrianglesShaderProgram(std::shared_ptr<ShaderProgram> program) {
    d2.program = program;
}

void GL::VertexArrayKit::setEnabled(bool d0, bool d1, bool d2) {
    this->d0.enabled = d0;
    this->d1.enabled = d1;
    this->d2.enabled = d2;
}
