template <typename S, class IdAlloc, S defaultAlignment>
typename Buffer<S, IdAlloc, defaultAlignment>::Offset
Buffer<S, IdAlloc, defaultAlignment>::getAllocationOffset(Id id) {
    typename Rt::Allocator::Default<S, IdAlloc>::Range range;

    if (allocator.getAllocationInfo(id, &range))
        return range.offset;

    return 0;
}

template <typename S, class IdAlloc, S defaultAlignment>
Buffer<S, IdAlloc, defaultAlignment>::Buffer(S size, GLenum usage, Rt::Value::Map defaultRequirements) {
    Buffer::bind(Buffer::Target::CopyRead, this);
    data(Buffer::Target::CopyRead, size, 0, usage);

    this->allocator.init(size);
    this->usage = usage;

    this->setDefaultRequirements(Rt::Memory::CommonRequirements<S>::pack(Rt::Option<Size>(),
                                                                         Rt::Option<Size>(defaultAlignment)) + defaultRequirements);
}

template <typename S, class IdAlloc, S defaultAlignment>
Buffer<S, IdAlloc, defaultAlignment>::Buffer(Rt::Value::Map properties, Rt::Value::Map defaultRequirements) {
    auto size = properties.getScalar<S>("size");
    if (!size.defined) Rt::error(0xF82E0801);

    auto usage = properties.getScalar<GLenum>("usage");
    if (!usage.defined) Rt::error(0xBA164CAA);

    Buffer(size.value, usage.value, defaultRequirements);
}

template <typename S, class IdAlloc, S defaultAlignment>
typename Buffer<S, IdAlloc, defaultAlignment>::Id
Buffer<S, IdAlloc, defaultAlignment>::alloc(S size, S alignment) {
    return Rt::Memory::Traits::Alloc<Id>::alloc(Rt::Memory::CommonRequirements<Size>::pack(size, alignment));
}

template <typename S, class IdAlloc, S defaultAlignment>
typename Buffer<S, IdAlloc, defaultAlignment>::Id
Buffer<S, IdAlloc, defaultAlignment>::inheritedAlloc(Rt::Value::Map properties) {
    Rt::Option<S> size, alignment;

    Rt::Memory::CommonRequirements<S>::unpack(properties, size, alignment);
    if (!size.defined || !alignment.defined) Rt::error(0xD4C76F7A);

    auto id = this->allocator.alloc(size.get(), alignment.get());
    if (id != 0) return id;

    return 0;
}

template <typename S, class IdAlloc, S defaultAlignment>
void Buffer<S, IdAlloc, defaultAlignment>::free(Id id) {
    this->allocator.free(id);
}

template <typename S, class IdAlloc, S defaultAlignment>
void Buffer<S, IdAlloc, defaultAlignment>::getAllocationInfo(Id id, Offset* offset, S* size) {
    typename Rt::Allocator::Default<S, IdAlloc>::Range range;
    allocator.getAllocationInfo(id, &range);
    if (offset) *offset = range.offset;
    if (size) *size = range.size;
}

template <typename S, class IdAlloc, S defaultAlignment>
void Buffer<S, IdAlloc, defaultAlignment>::getInfo(S* size, S* allocatedSize, GLenum* usage) {
    this->allocator.getInfo(size, allocatedSize);
    if (usage) *usage = this->usage;
}

template <typename S, class IdAlloc, S defaultAlignment>
Rt::Value::Map Buffer<S, IdAlloc, defaultAlignment>::getInfo() {
    Rt::Value::Map info;
    S size, allocatedSize;
    GLenum usage;

    getInfo(&size, &allocatedSize, &usage);
    info.setScalar<bool>("isBounded", true);
    info.setScalar<S>("size", size);
    info.setScalar<S>("allocatedSize", allocatedSize);
    info.setScalar<GLenum>("usage", usage);
    info.setScalar<GLuint>("bufferId", getID());

    return info;
}

template <typename S, class IdAlloc, S defaultAlignment>
Rt::Value::Map Buffer<S, IdAlloc, defaultAlignment>::getAllocationInfo(Id ID) {
    Rt::Value::Map info;
    S offset, size;

    getAllocationInfo(ID, &offset, &size);
    info.setScalar<S>("offset", offset);
    info.setScalar<S>("size", size);

    return info;
}
