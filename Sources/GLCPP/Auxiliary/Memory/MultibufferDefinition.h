template <typename S, class IdAlloc, class A, S defaultAlignment>
Rt::Value::Map Multibuffer<S, IdAlloc, A, defaultAlignment>::inheritedGenerateAllocatorProperties(Rt::Value::Map requirements) {
    Rt::Value::Map properties = Rt::Memory::Multibuffer::Alloc<S, IdAlloc, A, defaultAlignment>::inheritedGenerateAllocatorProperties(requirements);
    auto usage = requirements.getScalar<GLenum>("usage");
    if (usage.defined) properties.setScalar<GLenum>("usage", usage);
    return properties;
}

template <typename S, class IdAlloc, class A, S defaultAlignment>
bool Multibuffer<S, IdAlloc, A, defaultAlignment>::doAllocatorSatisfyRequirements(A* allocator, Rt::Value::Map requirements) {
    auto allocationUsage = requirements.getScalar<GLenum>("usage");
    if (allocationUsage.defined) {
        Rt::Value::Map allocatorInfo = allocator->getInfo();

        auto allocatorUsage = allocatorInfo.getScalar<GLenum>("usage");
        if (!allocatorUsage.defined) Rt::error(0x4D159040);

        if (allocationUsage.get() != allocatorUsage.get()) return false;
    }

    return Rt::Memory::Multibuffer::Alloc<S, IdAlloc, A, defaultAlignment>::doAllocatorSatisfyRequirements(allocator, requirements);
}

template <typename S, class IdAlloc, class A, S defaultAlignment>
Multibuffer<S, IdAlloc, A, defaultAlignment>::Multibuffer(Size bufferSize, Rt::Value::Map defaultAllocatorsProperties,
                                                                           Rt::Value::Map defaultAllocationsRequirements) :
    Rt::Memory::Multibuffer::Alloc<S, IdAlloc, A, defaultAlignment>(bufferSize, defaultAllocatorsProperties, defaultAllocationsRequirements)
{}

template <typename S, class IdAlloc, class A, S defaultAlignment>
typename Multibuffer<S, IdAlloc, A, defaultAlignment>::Id
Multibuffer<S, IdAlloc, A, defaultAlignment>::alloc(Size size, GLenum usage, Size alignment)
{
    Rt::Value::Map requirements = Rt::Memory::CommonRequirements<S>::pack(size, alignment);
    requirements.setScalar<GLenum>("usage", usage);
    return Rt::Memory::Traits::Alloc<Id>::alloc(requirements);
}
/*
template <typename S, class IdAlloc, class A, S defaultAlignment>
Rt::Value::Map
Multibuffer<S, IdAlloc, A, defaultAlignment>::getAllocationInfo(Id id) {
    Rt::Value::Map info;
    S size, offset;
    GLenum usage;

    getInfo(&size, &allocatedSize, &usage);
    info.setScalar<S>("size", size);
    info.setScalar<S>("offset", offset);
    info.setScalar<GLenum>("usage", usage);

    return info;
}
*/