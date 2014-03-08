template <typename A>
Allocation<A>::Allocation(std::shared_ptr<A> allocator) : Allocation() {
	this->allocator = allocator;
}

template <typename A>
Allocation<A>::Allocation(std::shared_ptr<A> allocator, typename A::Id id) : Allocation(allocator) {
    this->allocator = allocator;
    this->id = id;
}

template <typename A>
Allocation<A>::~Allocation() {
    if (allocator.get() && id != IDAllocator::Trait<typename A::Id>::none)
        allocator->free(id);
}

template <typename A>
std::shared_ptr<A> Allocation<A>::getAllocator() const {
    return allocator;
}

template <typename A>
typename A::Id Allocation<A>::getId() const {
    return id;
}

template <typename A>
void Allocation<A>::instantiate(Value::Map requirements) {
    if (id != IDAllocator::Trait<typename A::Id>::none)
        allocator->free(id);

    id = static_cast<Rt::Memory::Traits::Alloc<typename A::Id>*>(allocator.get())->alloc(requirements);
    if (id == IDAllocator::Trait<typename A::Id>::none)
        error(0x0778374C);
}

template <typename A>
Value::Map Allocation<A>::getInfo() {
    return allocator->getAllocationInfo(id);
}
