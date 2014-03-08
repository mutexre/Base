template <typename Size, class IdAlloc, Size defaultAlignment>
void* Malloc<Size, IdAlloc, defaultAlignment>::getAllocationPtr(Id id) {
    auto allocationIterator = allocations.find(id);
    if (allocationIterator != allocations.end())
        return (*allocationIterator).second.dataPtr;

    return 0;
}

template <typename Size, class IdAlloc, Size defaultAlignment>
Malloc<Size, IdAlloc, defaultAlignment>::Malloc() : Malloc(Value::Map())
{}

template <typename Size, class IdAlloc, Size defaultAlignment>
Malloc<Size, IdAlloc, defaultAlignment>::Malloc(Value::Map defaultRequirements) {
    this->setDefaultRequirements(CommonRequirements<Size>::pack(Option<Size>(), Option<Size>(defaultAlignment)) + defaultRequirements);
}

template <typename Size, class IdAlloc, Size defaultAlignment>
Malloc<Size, IdAlloc, defaultAlignment>::~Malloc() {
    for (std::pair<Id, Allocation> allocation : allocations)
        ::free(allocation.second.ptr);
}

template <typename Size, class IdAlloc, Size defaultAlignment>
typename Malloc<Size, IdAlloc, defaultAlignment>::Id
Malloc<Size, IdAlloc, defaultAlignment>::alloc(Size size) {
    return Traits::Alloc<Id>::alloc(CommonRequirements<Size>::pack(size));
}

template <typename Size, class IdAlloc, Size defaultAlignment>
typename Malloc<Size, IdAlloc, defaultAlignment>::Id
Malloc<Size, IdAlloc, defaultAlignment>::alloc(Size size, Size alignment) {
    return Traits::Alloc<Id>::alloc(CommonRequirements<Size>::pack(size, alignment));
}

template <typename Size, class IdAlloc, Size defaultAlignment>
typename Malloc<Size, IdAlloc, defaultAlignment>::Id
Malloc<Size, IdAlloc, defaultAlignment>::inheritedAlloc(Value::Map properties) {
    Option<Size> size, alignment;
    Id id;

    CommonRequirements<Size>::unpack(properties, size, alignment);
    if (!size.defined || !alignment.defined) error(0x53164112);

    if (this->idAllocator.get(&id)) {
        u1* ptr = (u1*)malloc(size.value + alignment.value - 1);
        if (ptr) {
            auto alignedDataOffset = ((alignment.value - (((u8)ptr) % alignment.value)) % alignment.value);
            allocations[id] = Allocation(ptr, ptr + alignedDataOffset);
            return id;
        }
        else
            this->idAllocator.put(id);
    }

    return 0;
}

template <typename Size, class IdAlloc, Size defaultAlignment>
void Malloc<Size, IdAlloc, defaultAlignment>::free(Id id) {
    auto allocationIterator = allocations.find(id);
    if (allocationIterator != allocations.end())
    {
        ::free((*allocationIterator).second.ptr);
        allocations.erase(allocationIterator);
        this->idAllocator.put(id);
    }
    else
        error(0x42706B7B);
}

template <typename Size, class IdAlloc, Size defaultAlignment>
void* Malloc<Size, IdAlloc, defaultAlignment>::map(Id id) {
    return getAllocationPtr(id);
}

template <typename Size, class IdAlloc, Size defaultAlignment>
void Malloc<Size, IdAlloc, defaultAlignment>::unmap(Id id) {
}

template <typename Size, class IdAlloc, Size defaultAlignment>
void Malloc<Size, IdAlloc, defaultAlignment>::read(Id id, Size offset, Size size, void* ptr) {
    auto allocationPtr = getAllocationPtr(id);
    if (allocationPtr) memcpy(ptr, ((char*)allocationPtr) + size, size);
}

template <typename Size, class IdAlloc, Size defaultAlignment>
void Malloc<Size, IdAlloc, defaultAlignment>::write(Id id, Size offset, Size size, const void* ptr) {
    auto allocationPtr = getAllocationPtr(id);
    if (allocationPtr) memcpy(((char*)allocationPtr) + size, ptr, size);
}

template <typename Size, class IdAlloc, Size defaultAlignment>
Value::Map Malloc<Size, IdAlloc, defaultAlignment>::getInfo() {
    Value::Map info;
    info.setScalar<bool>("isBounded", false);
    return info;
}
