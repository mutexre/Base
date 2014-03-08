template <class A>
Value::Map Alloc<A>::generateAllocatorProperties(Value::Map requirements) {
    return this->getDefaultAllocatorsProperties() + inheritedGenerateAllocatorProperties(requirements);
}

template <class A>
Value::Map Alloc<A>::inheritedGenerateAllocatorProperties(Value::Map requirements) {
    return Value::Map();
}

template <class A>
A* Alloc<A>::createAllocator(Value::Map properties) {
    return new A(properties);
}

template <class A>
typename Alloc<A>::Id Alloc<A>::tryAlloc(A* allocator, Value::Map& requirements) {
    auto ID = static_cast<Traits::Alloc<Id>*>(allocator)->alloc(requirements);
    if (ID != IdAllocator::none) {
        Id allocationId;
        if (idAlloc.get(&allocationId)) {
            this->ids2allocations[allocationId] = std::pair<A*, Id>(allocator, ID);
            return allocationId;
        }
        else {
            allocator->free(ID);
            return IdAllocator::none;
        }
    }
    return ID;
};

template <class A>
typename Alloc<A>::Id Alloc<A>::inheritedAlloc(Value::Map requirements)
{
    for (auto allocator : allocators) {
        if (doAllocatorSatisfyRequirements(allocator, requirements)) {
            auto id = tryAlloc(allocator, requirements);
            if (id != IdAllocator::none) return id;
        }
    }

    auto allocator = createAllocator(generateAllocatorProperties(requirements));
    if (!allocator) error(0xF4979436);

    allocators.push_front(allocator);

    return tryAlloc(allocator, requirements);
}

template <class A>
Alloc<A>::Alloc(Value::Map defaultAllocatorsProperties, Value::Map defaultAllocationsRequirements) {
    this->setDefaultAllocatorsProperties(defaultAllocatorsProperties);
    this->setDefaultRequirements(defaultAllocationsRequirements);
}

template <class A> Alloc<A>::~Alloc() {
    for (auto allocator : allocators) delete allocator;
}

template <class A>
Value::Map Alloc<A>::getDefaultAllocatorsProperties() {
    return defaultAllocatorsProperties;
}

template <class A>
void Alloc<A>::setDefaultAllocatorsProperties(Value::Map r) {
    this->defaultAllocatorsProperties = r;
}

template <class A>
void Alloc<A>::free(Id ID) {
    auto iter = this->ids2allocations.find(ID);
    if (iter != this->ids2allocations.end()) {
        auto& allocationInfo = (*iter).second;
        allocationInfo.first->free(allocationInfo.second);
    }
    else
        error(0x9570B15D);
}
