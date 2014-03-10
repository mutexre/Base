#include <GLCPP/GL.h>

GL::VertexArrayKit::VertexArrayKit(Options points,
                                   Options lines,
                                   Options triangles)
{
    setPointsOptions(points);
    setLinesOptions(lines);
    setTrianglesOptions(triangles);
}

void GL::VertexArrayKit::render()
{
#if defined __APPLE__ && TARGET_OS_IPHONE
    if (lines.enabled) {
        lines.bind();
        glDrawElements(GL_LINES,
                       verticesPerTriangle * lines.count,
                       lines.type,
                       (const GLchar*)lines.offset);
    }

    if (triangles.enabled) {
        triangles.bind();
        glDrawElements(GL_TRIANGLES,
                       verticesPerTriangle * triangles.count,
                       triangles.type,
                       (const GLchar*)triangles.offset);
    }
#else
        if (triangles.enabled)
        {
            triangles.bind();
            if (triangles.baseVertex > 0) {
                if (triangles.numberOfInstances > 1)
                    glDrawElementsInstancedBaseVertex(GL_TRIANGLES,
                                                      verticesPerTriangle * triangles.count,
                                                      triangles.type,
                                                      (const GLchar*)triangles.offset,
                                                      triangles.numberOfInstances,
                                                      triangles.baseVertex);
                else
                    glDrawElementsBaseVertex(GL_TRIANGLES,
                                             verticesPerTriangle * triangles.count,
                                             triangles.type,
                                             (const GLchar*)triangles.offset,
                                             triangles.baseVertex);
            }
            else {
                if (triangles.numberOfInstances > 1)
                    glDrawElementsInstanced(GL_TRIANGLES,
                                            GL::verticesPerTriangle * triangles.count,
                                            triangles.type,
                                            (const GLchar*)triangles.offset,
                                            triangles.numberOfInstances);
                else
                    glDrawElements(GL_TRIANGLES,
                                   GL::verticesPerTriangle * triangles.count,
                                   triangles.type,
                                   (const GLchar*)triangles.offset);
            }
        }

        if (lines.enabled)
        {
            lines.bind();
            if (lines.baseVertex > 0)
            {
                if (lines.numberOfInstances > 1)
                    glDrawElementsInstancedBaseVertex(GL_LINES,
                                                      GL::verticesPerEdge * lines.count,
                                                      lines.type,
                                                      (const GLchar*)lines.offset,
                                                      lines.numberOfInstances,
                                                      lines.baseVertex);
                else
                    glDrawElementsBaseVertex(GL_LINES,
                                             GL::verticesPerEdge * lines.count,
                                             lines.type,
                                             (const GLchar*)lines.offset,
                                             lines.baseVertex);
            }
            else {
                if (lines.numberOfInstances > 1)
                    glDrawElementsInstanced(GL_LINES,
                                            GL::verticesPerEdge * lines.count,
                                            lines.type,
                                            (const GLchar*)lines.offset,
                                            lines.numberOfInstances);
                else
                    glDrawElements(GL_LINES,
                                   GL::verticesPerEdge * lines.count,
                                   lines.type,
                                   (const GLchar*)lines.offset);
            }
        }
#endif

    if (points.enabled) {
        points.bind();
        glDrawArrays(GL_POINTS, points.offset, points.count);
    }
}

GL::VertexArrayKit::Options GL::VertexArrayKit::getPointsOptions() const {
    return points;
}

void GL::VertexArrayKit::setPointsOptions(Options options) {
    points = options;
}

void GL::VertexArrayKit::setPointsShaderProgram(std::shared_ptr<ShaderProgram> program) {
    points.program = program;
}

GL::VertexArrayKit::Options GL::VertexArrayKit::getLinesOptions() const {
    return lines;
}

void GL::VertexArrayKit::setLinesOptions(Options options) {
    lines = options;
}

void GL::VertexArrayKit::setLinesShaderProgram(std::shared_ptr<ShaderProgram> program) {
    lines.program = program;
}

GL::VertexArrayKit::Options GL::VertexArrayKit::getTrianglesOptions() const {
    return triangles;
}

void GL::VertexArrayKit::setTrianglesOptions(Options options) {
    triangles = options;
}

void GL::VertexArrayKit::setTrianglesShaderProgram(std::shared_ptr<ShaderProgram> program) {
    triangles.program = program;
}

void GL::VertexArrayKit::setEnabled(bool points, bool lines, bool triangles) {
    this->points.enabled = points;
    this->lines.enabled = lines;
    this->triangles.enabled = triangles;
}
