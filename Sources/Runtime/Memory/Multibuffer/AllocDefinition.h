template <typename S, class IdAlloc, class A, S defaultAlignment>
Value::Map Alloc<S, IdAlloc, A, defaultAlignment>::inheritedGenerateAllocatorProperties(Value::Map requirements) {
    Value::Map properties;

    auto size = requirements.getScalar<S>("size");
    if (!size.defined) error(0xB1911018);

    properties.setScalar<S>("size", Option<S>(((size.value - 1) / bufferSize + 1) * bufferSize));

    return properties;
}

template <typename S, class IdAlloc, class A, S defaultAlignment>
bool Alloc<S, IdAlloc, A, defaultAlignment>::doAllocatorSatisfyRequirements(A* allocator, Value::Map requirements) {
    Option<S> requiredSize, requiredAlignment;

    CommonRequirements<S>::unpack(requirements, requiredSize, requiredAlignment);
    if (!requiredSize.defined) error(0x35102098);

    Value::Map allocatorInfo = allocator->getInfo();

    auto isBounded = allocatorInfo.getScalar<bool>("isBounded");
    if (!(isBounded.defined && !isBounded.get())) {
        auto size = allocatorInfo.getScalar<S>("size");
        if (!size.defined) error(0xFFF09448);

        auto allocatedSize = allocatorInfo.getScalar<S>("allocatedSize");
        if (!allocatedSize.defined) error(0x59D93ADB);

        return (size.get() - allocatedSize.get()) >= (requiredSize.value + (requiredAlignment.defined ? requiredAlignment.value : defaultAlignment) - 1);
    }

    return true;
}

template <typename S, class IdAlloc, class A, S defaultAlignment>
Alloc<S, IdAlloc, A, defaultAlignment>::Alloc(Size bufferSize,
                                              Value::Map defaultAllocatorsProperties,
                                              Value::Map defaultAllocationsRequirements) :
    Compound::Alloc<A>(defaultAllocatorsProperties, defaultAllocationsRequirements)
{
    this->bufferSize = bufferSize;
}
