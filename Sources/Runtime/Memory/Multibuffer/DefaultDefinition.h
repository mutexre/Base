template <typename S, class IdAlloc, class B>
Default<S, IdAlloc, B>::Default(Size bufferSize, Value::Map allocators, Value::Map allocations) :
    Alloc<S, IdAlloc, B>(bufferSize, allocators, allocations)
{}
