Instance::Instance(std::shared_ptr<ShaderProgram> program,
                   std::shared_ptr<BindingPoint> bindingPoint)
{
    index = glGetUniformBlockIndex(program->getID(), Description::name);
    if (index == GL_INVALID_INDEX) Rt::error(0x3D63FC01);

    this->program = program;
    this->bindingPoint = bindingPoint;
}

std::shared_ptr<GL::UniformBlock::BindingPoint>
Instance::getBindingPoint() const {
    return bindingPoint;
}

void Instance::setBindingPoint(std::shared_ptr<BindingPoint> bindingPoint) {
    this->bindingPoint = bindingPoint;
    glUniformBlockBinding(program->getID(), index, bindingPoint->getBinding());
}

void Instance::bind() const {
    bindingPoint->bind();
}

void Instance::prepare(Buffer::Access access) {
    bindingPoint->bind();
    mappingPtr = bindingPoint->map(access);
}

void Instance::complete() {
    BindingPoint::unmap();
    BindingPoint::unbind();
}

template <typename T>
T Instance::getScalar(const std::string& name) {
    return *UNIFORM_PTR2(ptr, layout, var, T);
    return UniformBlock::getScalar<Description, T>(mappingPtr, layout.get(), var);
}

template <typename T>
void Instance::setScalar(const std::string& name, T value) {
    UniformBlock::setScalar<Description, T>(mappingPtr, layout.get(), var, value);
}

template <typename T>
void Instance::setArray(const std::string& name, T* values, Rt::u4 offset, Rt::u4 count, Rt::u4 stride) {
    UniformBlock::setArray<Description, T>(mappingPtr, layout.get(), var, values, offset, count, stride);
}

template <typename T>
void Instance::setMatrix(const std::string& name,
                         T* values,
                         bool srcIsRowMajor,
                         Rt::u4 nRows, Rt::u4 nColumns,
                         Rt::u4 rowStride, Rt::u4 columnStride)
{
    UniformBlock::setMatrix<Description, T>(mappingPtr, layout.get(), var, values, srcIsRowMajor, nRows, nColumns, rowStride, columnStride);
}
