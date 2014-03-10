#include <GLCPP/GL.h>

void GL::VertexArrayKit::Options::init(bool enabled, unsigned int offset, unsigned int count, GLenum type,
                                       GLint baseVertex, GLsizei numberOfInstances,
                                       Rt::Option<std::shared_ptr<ShaderProgram>> program,
                                       Rt::Option<std::shared_ptr<VertexArray>> array,
                                       Rt::Option<std::set<std::shared_ptr<GL::UniformBlock::BindingPoint>>> bindingPoints)
{
    this->enabled = enabled;
    this->offset = offset;
    this->count = count;
    this->type = type;
    this->baseVertex = baseVertex;
    this->numberOfInstances = numberOfInstances;

    if (program.defined)
        this->program = program.get();

    if (array.defined)
        this->array = array.get();
    else
        this->array = std::make_shared<VertexArray>();

    if (bindingPoints.defined)
        this->bindingPoints = bindingPoints.get();
}

GL::VertexArrayKit::Options::Options(bool enabled, unsigned int offset, unsigned int count, GLenum type,
                                     GLint baseVertex, GLsizei numberOfInstances,
                                     Rt::Option<std::shared_ptr<ShaderProgram>> program,
                                     Rt::Option<std::shared_ptr<VertexArray>> array,
                                     Rt::Option<std::set<std::shared_ptr<GL::UniformBlock::BindingPoint>>> bindingPoints)
{
	init(enabled, offset, count, type, baseVertex, numberOfInstances, program, array, bindingPoints);
}

GL::VertexArrayKit::Options::Options(bool enabled, unsigned int offset, unsigned int count, GLenum type,
                                     GLint baseVertex, GLsizei numberOfInstances,
                                     std::shared_ptr<ShaderProgram> program,
                                     Rt::Option<std::shared_ptr<VertexArray>> array,
                                     Rt::Option<std::set<std::shared_ptr<GL::UniformBlock::BindingPoint>>> bindingPoints)
{
    init(enabled, offset, count, type, baseVertex, numberOfInstances,
         Rt::Option<std::shared_ptr<ShaderProgram>>(program),
         array,
         bindingPoints);
}

GL::VertexArrayKit::Options::Options(bool enabled, unsigned int offset, unsigned int count, GLenum type,
                                     GLint baseVertex, GLsizei numberOfInstances,
                                     std::shared_ptr<ShaderProgram> program,
                                     std::shared_ptr<VertexArray> array,
                                     Rt::Option<std::set<std::shared_ptr<GL::UniformBlock::BindingPoint>>> bindingPoints)
{
	init(enabled, offset, count, type, baseVertex, numberOfInstances,
         Rt::Option<std::shared_ptr<ShaderProgram>>(program),
         Rt::Option<std::shared_ptr<VertexArray>>(array),
         bindingPoints);
}

GL::VertexArrayKit::Options::Options(bool enabled, unsigned int offset, unsigned int count, GLenum type,
                                     GLint baseVertex, GLsizei numberOfInstances,
                                     std::shared_ptr<ShaderProgram> program,
                                     std::shared_ptr<VertexArray> array,
                                     std::set<std::shared_ptr<GL::UniformBlock::BindingPoint>> bindingPoints)
{
    init(enabled, offset, count, type, baseVertex, numberOfInstances,
         Rt::Option<std::shared_ptr<ShaderProgram>>(program),
         Rt::Option<std::shared_ptr<VertexArray>>(array),
         Rt::Option<BindingPoints>(bindingPoints));
}

void GL::VertexArrayKit::Options::bind() {
    for (auto& bp : bindingPoints) bp->bind();
    VertexArray::bind(array.get());
    ShaderProgram::bind(program.get());
}
