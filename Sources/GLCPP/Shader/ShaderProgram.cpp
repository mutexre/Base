#include <string.h>
#include <GLCPP/GL.h>

#define GET_PARAMETER_BY_NAME(container, type, parameter) \
    auto x = container.find(name); \
    if (x != container.end()) \
        return Rt::Option<type>((*x).parameter); \
    \
    return Rt::Option<type>();

#define GET_PARAMETER_BY_INDEX(container, type, parameter) \
    auto x = container.get<Index>().find(index); \
    if (x != container.get<Index>().end()) \
        return Rt::Option<type>((*x).parameter); \
    \
    return Rt::Option<type>();

#define GET_UNIFORM_PARAMETER_BY_NAME(type, parameter) GET_PARAMETER_BY_NAME(uniforms, type, parameter)
#define GET_UNIFORM_PARAMETER_BY_INDEX(type, parameter) GET_PARAMETER_BY_INDEX(uniforms, type, parameter)

#define GET_UNIFORM_BLOCK_PARAMETER_BY_NAME(type, parameter) GET_PARAMETER_BY_NAME(uniformBlocks, type, parameter)
#define GET_UNIFORM_BLOCK_PARAMETER_BY_INDEX(type, parameter) GET_PARAMETER_BY_INDEX(uniformBlocks, type, parameter)

GL::ShaderProgram::Sources::Sources(std::string vertex, std::string fragment) {
    this->vertex = vertex;
    this->fragment = fragment;
}

GL::ShaderProgram::Sources::Sources(std::string vertex, std::string geometry, std::string fragment) : Sources(vertex, fragment) {
    this->geometry.define(geometry);
}

void GL::ShaderProgram::bind(GLuint ID) {
    glUseProgram(ID);
}

void GL::ShaderProgram::bind(const ShaderProgram& shaderProgram) {
    bind(shaderProgram.getID());
}

void GL::ShaderProgram::bind(const ShaderProgram* shaderProgram) {
    bind(shaderProgram->getID());
}

void GL::ShaderProgram::unbind() {
    bind(GLuint(0));
}

void GL::ShaderProgram::bind() {
    bind(ID);
}

GL::ShaderProgram::ShaderProgram() {
    type = Object::Type::ShaderProgram;
	ID = glCreateProgram();
	if (!ID) Rt::error(0xD15229FC);
    needToDelete = true;
}

GLint GL::ShaderProgram::getCurrentProgram() {
    GLint program;
    glGetIntegerv(GL_CURRENT_PROGRAM, &program);
    return program;
}

void GL::ShaderProgram::loadAttributes()
{
    struct Info {
        GLint count;
        GLint maxLength;
    }
    info;

    info.count = getInfo(GL_ACTIVE_ATTRIBUTES);
    info.maxLength = getInfo(GL_ACTIVE_ATTRIBUTE_MAX_LENGTH);

    attributes.clear();

    std::unique_ptr<GLchar[]> name = std::unique_ptr<GLchar[]>(new GLchar[info.maxLength + 1]);
    memset(name.get(), 0, info.maxLength);
    for (int i = 0; i < info.count; i++) {
        Attribute attr;

        glGetActiveAttrib(ID, i, info.maxLength + 1, nullptr, &attr.size, &attr.type, name.get());
        attr.name = name.get();
        attr.index = i;
        attr.location = glGetAttribLocation(ID, name.get());

        attributes.insert(attr);
    }
}

void GL::ShaderProgram::loadUniforms()
{
    struct Info {
        GLint count;
        GLint maxLength;
    }
    info;

    info.count = getInfo(GL_ACTIVE_UNIFORMS);
    info.maxLength = getInfo(GL_ACTIVE_UNIFORM_MAX_LENGTH);

    uniforms.clear();

    std::unique_ptr<GLchar[]> name = std::unique_ptr<GLchar[]>(new GLchar[info.maxLength + 1]);
    memset(name.get(), 0, info.maxLength);
    for (int i = 0; i < info.count; i++) {
        Uniform uniform;

        glGetActiveUniform(ID, i, info.maxLength + 1, nullptr, &uniform.size, &uniform.type, name.get());
        uniform.name = name.get();
        uniform.index = i;

        glGetActiveUniformsiv(ID, 1, (const GLuint*)&i, GL_UNIFORM_BLOCK_INDEX, &uniform.blockIndex);
        glGetActiveUniformsiv(ID, 1, (const GLuint*)&i, GL_UNIFORM_OFFSET, &uniform.offset);
        glGetActiveUniformsiv(ID, 1, (const GLuint*)&i, GL_UNIFORM_ARRAY_STRIDE, &uniform.arrayStride);
        glGetActiveUniformsiv(ID, 1, (const GLuint*)&i, GL_UNIFORM_MATRIX_STRIDE, &uniform.matrixStride);
        glGetActiveUniformsiv(ID, 1, (const GLuint*)&i, GL_UNIFORM_IS_ROW_MAJOR, &uniform.isRowMajor);

        uniform.location = glGetUniformLocation(ID, name.get());

        uniforms.insert(uniform);
    }
}

void GL::ShaderProgram::loadUniformBlocks() {
    struct Info {
        GLint count;
        GLint maxLength;
    }
    info;

    info.count = getInfo(GL_ACTIVE_UNIFORM_BLOCKS);
    info.maxLength = getInfo(GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH);

    uniformBlocks.clear();

    std::unique_ptr<GLchar[]> name = std::unique_ptr<GLchar[]>(new GLchar[info.maxLength + 1]);
    memset(name.get(), 0, info.maxLength);
    for (int i = 0; i < info.count; i++) {
        UniformBlock uniformBlock;
        GLint activeUniformsCount;

        glGetActiveUniformBlockName(ID, i, info.maxLength + 1, nullptr, name.get());
        uniformBlock.name = name.get();
        uniformBlock.index = i;

        glGetActiveUniformBlockiv(ID, i, GL_UNIFORM_BLOCK_BINDING, &uniformBlock.binding);
        glGetActiveUniformBlockiv(ID, i, GL_UNIFORM_BLOCK_DATA_SIZE, &uniformBlock.dataSize);
        glGetActiveUniformBlockiv(ID, i, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &activeUniformsCount);

        std::vector<GLint> activeUniforms(activeUniformsCount);
        glGetActiveUniformBlockiv(ID, i, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, activeUniforms.data());

        for (auto uniformIndex : activeUniforms)
            uniformBlock.activeUniforms.left.insert(std::pair<GLint, std::string>(uniformIndex, getUniformName(uniformIndex).get()));

        glGetActiveUniformBlockiv(ID, i, GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER, &uniformBlock.referencedBy.vertex);
        glGetActiveUniformBlockiv(ID, i, GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER, &uniformBlock.referencedBy.fragment);
        glGetActiveUniformBlockiv(ID, i, GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER, &uniformBlock.referencedBy.geometry);

        uniformBlocks.insert(uniformBlock);
    }
}

void GL::ShaderProgram::loadTFVaryings()
{
    struct Info {
        GLint count;
        GLint maxLength;
    }
    info;

    info.count = getInfo(GL_TRANSFORM_FEEDBACK_VARYINGS);
    info.maxLength = getInfo(GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH);

    tfVaryings.clear();

    std::unique_ptr<GLchar[]> name = std::unique_ptr<GLchar[]>(new GLchar[info.maxLength + 1]);
    memset(name.get(), 0, info.maxLength);
    for (int i = 0; i < info.count; i++) {
        TFVarying tfVarying;
        glGetTransformFeedbackVarying(ID, i, info.maxLength + 1, nullptr, &tfVarying.size, &tfVarying.type, name.get());
        tfVaryings[name.get()] = tfVarying;
    }
}

void GL::ShaderProgram::loadVariables() {
    loadAttributes();
    loadUniforms();
    loadUniformBlocks();
    loadTFVaryings();
}

void GL::ShaderProgram::setTransformFeedbackVaryings(TFVaryingNames vars, GLenum bufferMode) {
    if (!vars.empty()) {
        auto varyings = std::unique_ptr<const GLchar*[]>(new const GLchar*[vars.size()]);
        int i = 0;

        for (auto& name : vars)
            varyings[i++] = name.c_str();

        setTransformFeedbackVaryings(vars.size(), varyings.get(), bufferMode);
    }
}

void GL::ShaderProgram::init(std::shared_ptr<VertexShader> vertexShader,
                             Rt::Option<std::shared_ptr<GeometryShader>> geometryShader,
                             std::shared_ptr<FragmentShader> fragmentShader,
                             FragDataLocations fragDataLocations,
                             TFVaryingNames separate,
                             TFVaryingNames interleaved)
{
    glAttachShader(ID, vertexShader->getID());
    if (geometryShader.defined) glAttachShader(ID, geometryShader.get()->getID());
    glAttachShader(ID, fragmentShader->getID());

    for (auto& f : fragDataLocations)
        bindFragDataLocation(f.first, f.second);

    setTransformFeedbackVaryings(separate, GL_SEPARATE_ATTRIBS);
    setTransformFeedbackVaryings(interleaved, GL_INTERLEAVED_ATTRIBS);

    link();
    loadVariables();

    shaders.vertex = vertexShader;
    shaders.fragment = fragmentShader;
}

GL::ShaderProgram::ShaderProgram(std::shared_ptr<VertexShader> vertexShader,
                                 Rt::Option<std::shared_ptr<GeometryShader>> geometryShader,
                                 std::shared_ptr<FragmentShader> fragmentShader,
                                 FragDataLocations fragDataLocations,
                                 TFVaryingNames separate,
                                 TFVaryingNames interleaved)
    : ShaderProgram()
{
    init(vertexShader, geometryShader, fragmentShader, fragDataLocations, separate, interleaved);
}

GL::ShaderProgram::ShaderProgram(Sources& src,
                                 FragDataLocations fragDataLocations,
                                 TFVaryingNames separate,
                                 TFVaryingNames interleaved)
    : ShaderProgram()
{
    init(std::make_shared<VertexShader>(src.vertex.c_str()),
         src.geometry.defined ? Rt::Option<std::shared_ptr<GeometryShader>>(std::make_shared<GeometryShader>(src.geometry.get().c_str())) :
                                Rt::Option<std::shared_ptr<GeometryShader>>(),
         std::make_shared<FragmentShader>(src.fragment.c_str()),
         fragDataLocations,
         separate, interleaved);
}

void GL::ShaderProgram::link() {
    GLint isLinked;

    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &isLinked);
    if (!isLinked) {
        GLsizei logLength;

        glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &logLength);
        if (logLength > 0) {
            GLsizei actualCompilationLogLength;

            auto log = new GLchar[logLength + 1];
            memset(log, 0, logLength + 1);

            glGetProgramInfoLog(ID, logLength, &actualCompilationLogLength, log);

            throw LinkError(log);
        }

        throw LinkError();
    }
}
/*
GL::ShaderProgram::ShaderProgram(ShaderProgram&& that) {
    ID = that.ID;
    needToDelete = that.needToDelete;

    shaders.vertex = that.shaders.vertex;
    shaders.geometry = that.shaders.geometry;
    shaders.fragment = that.shaders.fragment;

    attributes = that.attributes;
    uniforms = that.uniforms;
    uniformBlocks = that.uniformBlocks;
    tfVaryings = that.tfVaryings;

    that.needToDelete = false;
}
*/
GLint GL::ShaderProgram::getInfo(GLenum parameter) {
	GLint value;
	glGetProgramiv(ID, parameter, &value);
	return value;
}

void GL::ShaderProgram::enableAttribArray(GLint location) {
    glEnableVertexAttribArray(location);
}

void GL::ShaderProgram::enableAttribArray(std::string name) {
    auto attr = attributes.find(name);
    if (attr != attributes.end())
        enableAttribArray((*attr).location);
    else
        Rt::error(0x7C579290);
}

void GL::ShaderProgram::bindFragDataLocation(GLuint index, std::string name) {
#ifdef __APPLE__ && TARGET_OS_IPHONE
#else
    glBindFragDataLocation(ID, index, name.c_str());
#endif
}

void GL::ShaderProgram::setTransformFeedbackVaryings(GLsizei count, const GLchar** varyings, GLenum bufferMode) {
    glTransformFeedbackVaryings(ID, count, varyings, bufferMode);
}

const GL::ShaderProgram::Attributes& GL::ShaderProgram::getAttributes() const {
    return attributes;
}

const GL::ShaderProgram::Uniforms& GL::ShaderProgram::getUniforms() const {
    return uniforms;
}

const GL::ShaderProgram::UniformBlocks& GL::ShaderProgram::getUniformBlocks() const {
    return uniformBlocks;
}

const GL::ShaderProgram::TFVaryings& GL::ShaderProgram::getTFVaryings() const {
    return tfVaryings;
}

Rt::Option<GLint> GL::ShaderProgram::getAttributeLocation(std::string name) {
    auto attr = attributes.find(name);
    if (attr != attributes.end()) return Rt::Option<GLint>((*attr).location);
    return Rt::Option<GLint>();
}

// Uniforms

Rt::Option<GL::ShaderProgram::Uniform> GL::ShaderProgram::getUniform(GLuint index) {
    auto uniform = uniforms.get<Index>().find(index);
    if (uniform != uniforms.get<Index>().end())
        return Rt::Option<Uniform>(*uniform);

    return Rt::Option<Uniform>();
}

Rt::Option<GL::ShaderProgram::Uniform> GL::ShaderProgram::getUniform(std::string name) {
    auto uniform = uniforms.find(name);
    if (uniform != uniforms.end())
        return Rt::Option<Uniform>(*uniform);

    return Rt::Option<Uniform>();
}

Rt::Option<std::string> GL::ShaderProgram::getUniformName(GLint index) {
    auto uniform = uniforms.get<Index>().find(index);
    if (uniform != uniforms.get<Index>().end())
        return Rt::Option<std::string>((*uniform).name);

    return Rt::Option<std::string>();
}

Rt::Option<GLint> GL::ShaderProgram::getUniformIndex(std::string name) {
    auto uniform = uniforms.find(name);
    if (uniform != uniforms.end()) return Rt::Option<GLint>((*uniform).index);
    return Rt::Option<GLint>();
}

Rt::Option<GLint> GL::ShaderProgram::getUniformLocation(GLuint index) {
    GET_UNIFORM_PARAMETER_BY_INDEX(GLint, location)
}

Rt::Option<GLint> GL::ShaderProgram::getUniformLocation(std::string name) {
    GET_UNIFORM_PARAMETER_BY_NAME(GLint, location)
}

Rt::Option<GLenum> GL::ShaderProgram::getUniformType(GLuint index) {
    GET_UNIFORM_PARAMETER_BY_INDEX(GLenum, type)
}

Rt::Option<GLenum> GL::ShaderProgram::getUniformType(std::string name) {
    GET_UNIFORM_PARAMETER_BY_NAME(GLenum, type)
}

Rt::Option<GLint> GL::ShaderProgram::getUniformSize(GLuint index) {
    GET_UNIFORM_PARAMETER_BY_INDEX(GLint, size)
}

Rt::Option<GLint> GL::ShaderProgram::getUniformSize(std::string name) {
    GET_UNIFORM_PARAMETER_BY_NAME(GLint, size)
}

Rt::Option<GLint> GL::ShaderProgram::getBlockIndexOfUniform(GLuint index) {
    GET_UNIFORM_PARAMETER_BY_INDEX(GLint, blockIndex)
}

Rt::Option<GLint> GL::ShaderProgram::getBlockIndexOfUniform(std::string name) {
    GET_UNIFORM_PARAMETER_BY_NAME(GLint, blockIndex)
}

Rt::Option<GLint> GL::ShaderProgram::getUniformOffset(GLuint index) {
    GET_UNIFORM_PARAMETER_BY_INDEX(GLint, offset)
}

Rt::Option<GLint> GL::ShaderProgram::getUniformOffset(std::string name) {
    GET_UNIFORM_PARAMETER_BY_NAME(GLint, offset)
}

Rt::Option<GLint> GL::ShaderProgram::getUniformArrayStride(GLuint index) {
    GET_UNIFORM_PARAMETER_BY_INDEX(GLint, arrayStride)
}

Rt::Option<GLint> GL::ShaderProgram::getUniformArrayStride(std::string name) {
    GET_UNIFORM_PARAMETER_BY_NAME(GLint, arrayStride)
}

Rt::Option<GLint> GL::ShaderProgram::getUniformMatrixStride(GLuint index) {
    GET_UNIFORM_PARAMETER_BY_INDEX(GLint, matrixStride)
}

Rt::Option<GLint> GL::ShaderProgram::getUniformMatrixStride(std::string name) {
    GET_UNIFORM_PARAMETER_BY_NAME(GLint, matrixStride)
}

Rt::Option<GLint> GL::ShaderProgram::isUniformRowMajor(GLuint index) {
    GET_UNIFORM_PARAMETER_BY_INDEX(GLint, isRowMajor)
}

Rt::Option<GLint> GL::ShaderProgram::isUniformRowMajor(std::string name) {
    GET_UNIFORM_PARAMETER_BY_NAME(GLint, isRowMajor)
}

void GL::ShaderProgram::setAttribute(GLuint index, const Rt::u1* ptr) {
    auto attr = attributes.get<Index>().find(index);
    if (attr != attributes.get<Index>().end())
        (*attr).set(ptr);
    else
        Rt::error(0x42340860);
}

void GL::ShaderProgram::setAttribute(std::string name, const Rt::u1* ptr) {
    Attributes::iterator attr = attributes.find(name);
    if (attr != attributes.end())
        (*attr).set(ptr);
    else
        Rt::error(0xAA223829);
}

void GL::ShaderProgram::setUniform(GLuint index, const Rt::u1* ptr) {
    auto uniform = uniforms.get<Index>().find(index);
    if (uniform != uniforms.get<Index>().end())
        (*uniform).set(ptr);
    else
        Rt::error(0x4484EF86);
}

void GL::ShaderProgram::setUniform(std::string name, const Rt::u1* ptr) {
    Uniforms::iterator uniform = uniforms.find(name);
    if (uniform != uniforms.end())
        (*uniform).set(ptr);
    else
        Rt::error(0x12F32B6A);
}

// Uniform blocks

Rt::Option<GL::ShaderProgram::UniformBlock> GL::ShaderProgram::getUniformBlock(GLuint index) {
    auto uniformBlock = uniformBlocks.get<Index>().find(index);
    if (uniformBlock != uniformBlocks.get<Index>().end())
        return Rt::Option<UniformBlock>(*uniformBlock);

    return Rt::Option<GL::ShaderProgram::UniformBlock>();
}

Rt::Option<GL::ShaderProgram::UniformBlock> GL::ShaderProgram::getUniformBlock(std::string name) {
    auto uniformBlock = uniformBlocks.find(name);
    if (uniformBlock != uniformBlocks.end()) return Rt::Option<UniformBlock>(*uniformBlock);
    return Rt::Option<GL::ShaderProgram::UniformBlock>();
}

Rt::Option<GLint> GL::ShaderProgram::getUniformBlockIndex(std::string name) {
    auto uniformBlock = uniformBlocks.find(name);
    if (uniformBlock != uniformBlocks.end()) return Rt::Option<GLint>(uniformBlock->index);
    return Rt::Option<GLint>();
}

Rt::Option<GLint> GL::ShaderProgram::getUniformBlockName(GLuint index) {
    auto uniformBlock = uniformBlocks.get<Index>().find(index);
    if (uniformBlock != uniformBlocks.get<Index>().end())
        return Rt::Option<GLint>(uniformBlock->index);

    return Rt::Option<GLint>();
}

Rt::Option<GLint> GL::ShaderProgram::getUniformBlockDataSize(GLuint index) {
    GET_UNIFORM_BLOCK_PARAMETER_BY_INDEX(GLint, dataSize)
}

Rt::Option<GLint> GL::ShaderProgram::getUniformBlockDataSize(std::string name) {
    GET_UNIFORM_BLOCK_PARAMETER_BY_NAME(GLint, dataSize)
}

Rt::Option<GLint> GL::ShaderProgram::getUniformBlockBinding(GLuint index) {
    GET_UNIFORM_BLOCK_PARAMETER_BY_INDEX(GLint, binding)
}

Rt::Option<GLint> GL::ShaderProgram::getUniformBlockBinding(std::string name) {
    GET_UNIFORM_BLOCK_PARAMETER_BY_NAME(GLint, binding)
}

void GL::ShaderProgram::setUniformBlockBinding(GLuint index, GLuint binding) {
    auto uniformBlock = uniformBlocks.get<Index>().find(index);
    if (uniformBlock != uniformBlocks.get<Index>().end()) {
        glUniformBlockBinding(ID, uniformBlock->index, binding);
        uniformBlocks.get<Index>().modify(uniformBlock, [ &binding ](UniformBlock& ub) { ub.binding = binding; });
    }
    else
        Rt::error(0xB6C8FB98);
}

void GL::ShaderProgram::setUniformBlockBinding(std::string name, GLuint binding) {
    auto uniformBlock = uniformBlocks.find(name);
    if (uniformBlock != uniformBlocks.end()) {
        glUniformBlockBinding(ID, uniformBlock->index, binding);
        uniformBlocks.modify(uniformBlock, [ &binding ](UniformBlock& ub) { ub.binding = binding; });
    }
    else
        Rt::error(0x0BCDAAF3);
}

Rt::Option<GL::ShaderProgram::UniformBlock::ActiveUniforms>
GL::ShaderProgram::getUniformBlockActiveUniforms(GLuint index) {
    GET_UNIFORM_BLOCK_PARAMETER_BY_INDEX(UniformBlock::ActiveUniforms, activeUniforms)
}

Rt::Option<GL::ShaderProgram::UniformBlock::ActiveUniforms>
GL::ShaderProgram::getUniformBlockActiveUniforms(std::string name) {
    GET_UNIFORM_BLOCK_PARAMETER_BY_NAME(UniformBlock::ActiveUniforms, activeUniforms)
}

Rt::Option<GL::ShaderProgram::UniformBlock::ReferencedBy> GL::ShaderProgram::whichShadersReferenceUniformBlock(GLuint index) {
    GET_UNIFORM_BLOCK_PARAMETER_BY_INDEX(UniformBlock::ReferencedBy, referencedBy)
}

Rt::Option<GL::ShaderProgram::UniformBlock::ReferencedBy> GL::ShaderProgram::whichShadersReferenceUniformBlock(std::string name) {
    GET_UNIFORM_BLOCK_PARAMETER_BY_NAME(UniformBlock::ReferencedBy, referencedBy)
}

void GL::printShaderProgram(const ShaderProgram& program) {
    printShaderProgram(&program);
/*
    printf("Uniforms:\n");
    for (auto& x : program.getUniforms()) printUniform(x);

    printf("Uniform blocks:\n");
    for (auto& x : program.getUniformBlocks()) printUniformBlock(x);
*/
}

void GL::printShaderProgram(const ShaderProgram* program) {
    printf("Uniforms:\n");
    for (auto& x : program->getUniforms()) printUniform(x);

    printf("Uniform blocks:\n");
    for (auto& x : program->getUniformBlocks()) printUniformBlock(x);
}

void GL::printUniform(const GL::ShaderProgram::Uniform& x) {
    printf("  name: %s\n  index: %d\n  location: %d\n  type: %d\n  size: %d\n  block index: %d\n  offset: %d\n  array stride: %d\n  matrix stride: %d\n  row-major: %d\n\n",
           x.name.c_str(), x.index, x.location, x.type, x.size, x.blockIndex, x.offset, x.arrayStride, x.matrixStride, x.isRowMajor);
}

void GL::printUniformBlock(const GL::ShaderProgram::UniformBlock& x)
{
    printf("  name: %s\n  index: %d\n  data size: %d\n  binding: %d\n  referenced by:\n    vertex shader: %s\n    geometry: %s\n    fragment: %s\n",
           x.name.c_str(), x.index, x.dataSize, x.binding,
           x.referencedBy.vertex ? "yes" : "no",
           x.referencedBy.geometry ? "yes" : "no",
           x.referencedBy.fragment ? "yes" : "no");

    printf("  activeUniforms:\n");
    for (auto iter = x.activeUniforms.left.begin(); iter != x.activeUniforms.left.end(); iter++)
        printf("    %d <-> %s\n", iter->first, iter->second.c_str());
}
