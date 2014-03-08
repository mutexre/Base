template <typename Size, class IdAlloc, Size defaultAlignment>
void* Buffer<Size, IdAlloc, defaultAlignment>::getAllocationPtr(Id id) {
    typename Allocator::Default<Size, IdAlloc>::Range range;

    if (allocator.getAllocationInfo(id, &range))
        return buffer + range.offset;

    return 0;
}

template <typename Size, class IdAlloc, Size defaultAlignment>
Buffer<Size, IdAlloc, defaultAlignment>::Buffer(Size size, Value::Map defaultRequirements) {
    this->buffer = new u1[size];
    this->allocator.init(size);
    this->setDefaultRequirements(CommonRequirements<Size>::pack(Option<Size>(), Option<Size>(defaultAlignment)) + defaultRequirements);
}

template <typename Size, class IdAlloc, Size defaultAlignment>
Buffer<Size, IdAlloc, defaultAlignment>::Buffer(Value::Map properties, Value::Map defaultRequirements) :
    Buffer<Size, IdAlloc, defaultAlignment>(properties.getScalar<Size>("size").getOrElse([]() -> void { Rt::error(0xE75E83E1); }),
                                            defaultRequirements)
{
/*
    auto size = properties.getScalar<Size>("size");
    if (size.defined)
        Buffer<Size, IdAlloc, defaultAlignment>(size.get(), defaultRequirements);
    else
        error(0xF66E4327);
*/
}

template <typename Size, class IdAlloc, Size defaultAlignment>
Buffer<Size, IdAlloc, defaultAlignment>::~Buffer() {
    if (buffer) delete[] buffer;
}

template <typename Size, class IdAlloc, Size defaultAlignment>
typename Buffer<Size, IdAlloc, defaultAlignment>::Id
Buffer<Size, IdAlloc, defaultAlignment>::alloc(Size size) {
    return Traits::Alloc<Id>::alloc(CommonRequirements<Size>::pack(size));
}

template <typename Size, class IdAlloc, Size defaultAlignment>
typename Buffer<Size, IdAlloc, defaultAlignment>::Id
Buffer<Size, IdAlloc, defaultAlignment>::alloc(Size size, Size alignment) {
    return Traits::Alloc<Id>::alloc(CommonRequirements<Size>::pack(size, alignment));
}

template <typename Size, class IdAlloc, Size defaultAlignment>
typename Buffer<Size, IdAlloc, defaultAlignment>::Id
Buffer<Size, IdAlloc, defaultAlignment>::inheritedAlloc(Value::Map properties) {
    Option<Size> size, alignment;

    CommonRequirements<Size>::unpack(properties, size, alignment);
    if (!size.defined || !alignment.defined) error(0x53164112);

    auto id = this->allocator.alloc(size.value, alignment.value);
    if (id != 0) return id;

    return 0;
}

template <typename Size, class IdAlloc, Size defaultAlignment>
void Buffer<Size, IdAlloc, defaultAlignment>::free(Id id) {
    this->allocator.free(id);
}

template <typename Size, class IdAlloc, Size defaultAlignment>
void* Buffer<Size, IdAlloc, defaultAlignment>::map(Id id) {
    return getAllocationPtr(id);
}

template <typename Size, class IdAlloc, Size defaultAlignment>
void Buffer<Size, IdAlloc, defaultAlignment>::unmap(Id id) {
}

template <typename Size, class IdAlloc, Size defaultAlignment>
void Buffer<Size, IdAlloc, defaultAlignment>::read(Id id, Size offset, Size size, void* ptr) {
    auto allocationPtr = getAllocationPtr(id);
    if (allocationPtr) memcpy(ptr, ((char*)allocationPtr) + size, size);
}

template <typename Size, class IdAlloc, Size defaultAlignment>
void Buffer<Size, IdAlloc, defaultAlignment>::write(Id id, Size offset, Size size, const void* ptr) {
    auto allocationPtr = getAllocationPtr(id);
    if (allocationPtr) memcpy(((char*)allocationPtr) + size, ptr, size);
}

template <typename Size, class IdAlloc, Size defaultAlignment>
void Buffer<Size, IdAlloc, defaultAlignment>::getInfo(Size* size, Size* allocatedSize) {
    this->allocator.getInfo(size, allocatedSize);
}

template <typename Size, class IdAlloc, Size defaultAlignment>
void Buffer<Size, IdAlloc, defaultAlignment>::getAllocationInfo(Id ID, Offset* offset, Size* size) {
    this->allocator.getAllocationInfo(ID, offset, size);
}

template <typename Size, class IdAlloc, Size defaultAlignment>
Value::Map Buffer<Size, IdAlloc, defaultAlignment>::getInfo() {
    Value::Map info;
    Size size, allocatedSize;

    getInfo(&size, &allocatedSize);
    info.setScalar<bool>("isBounded", true);
    info.setScalar<Size>("size", size);
    info.setScalar<Size>("allocatedSize", allocatedSize);

    return info;
}

template <typename Size, class IdAlloc, Size defaultAlignment>
Value::Map Buffer<Size, IdAlloc, defaultAlignment>::getAllocationInfo(Id ID) {
    Value::Map info;
    Size offset, size;

    getAllocationInfo(ID, &offset, &size);
    info.setScalar<Size>("offset", offset);
    info.setScalar<Size>("size", size);

    return info;
}
