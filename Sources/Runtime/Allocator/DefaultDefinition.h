template <typename Size, class IdAlloc>
Rt::Allocator::Default<Size, IdAlloc>::Default() : allocatedSize(0)
{
}

template <typename Size, class IdAlloc>
bool Rt::Allocator::Default<Size, IdAlloc>::init(Size size)
{
    unused[0] = size;
    all[0] = size;

    this->size = size;

    return true;
}

template <typename Size, class IdAlloc>
typename Rt::Allocator::Default<Size, IdAlloc>::Id
Rt::Allocator::Default<Size, IdAlloc>::allocFirstFit(Size size, Size alignment)
{
    for (auto iter = unused.begin(); iter != unused.end(); iter++)
    {
        Range range(*iter);
        Offset headSize = (alignment - (range.offset % alignment)) % alignment;

        if (range.size - headSize >= size)
        {
            Id id;

            if (idAllocator.get(&id))
            {
                if (headSize > 0)
                {
                    unused[range.offset] = headSize;
                    all[range.offset] = headSize;
                }
                else
                    unused.erase(iter);

                allocated[id] = Range(range.offset + headSize, size);
                all[range.offset + headSize] = size;
                allocatedSize += size;

                auto tailSize = range.size - (headSize + size);
                if (tailSize > 0)
                {
                    unused[range.offset + headSize + size] = tailSize;
                    all[range.offset + headSize + size] = tailSize;
                }

                return id;
            }
            else
                return IdAlloc::none;
        }
    }

    return IdAlloc::none;
}

template <typename Size, class IdAlloc>
typename Rt::Allocator::Default<Size, IdAlloc>::Id
Rt::Allocator::Default<Size, IdAlloc>::allocNextFit(Size size)
{
    return IdAlloc::none;
}

template <typename Size, class IdAlloc>
typename Rt::Allocator::Default<Size, IdAlloc>::Id
Rt::Allocator::Default<Size, IdAlloc>::allocBestFit(Size size)
{
    return IdAlloc::none;
}

template <typename Size, class IdAlloc>
typename Rt::Allocator::Default<Size, IdAlloc>::Id
Rt::Allocator::Default<Size, IdAlloc>::allocWorstFit(Size size)
{
    return IdAlloc::none;
}

template <typename Size, class IdAlloc>
typename Rt::Allocator::Default<Size, IdAlloc>::Id
Rt::Allocator::Default<Size, IdAlloc>::alloc(Size size, Size alignment)
{
    return allocFirstFit(size, alignment);
}

template <typename Size, class IdAlloc>
void Rt::Allocator::Default<Size, IdAlloc>::findFreeNeighborRanges(Range range, NeighborRange& left, NeighborRange& right)
{
    for (auto jter = unused.begin();
         jter != unused.end() && !(left.exists && right.exists);
         jter++)
    {
        Range currentRange(*jter);

        if (!left.exists)
        {
            if (currentRange.offset + currentRange.size == range.offset)
                left = currentRange;
        }

        if (!right.exists)
        {
            if (currentRange.offset == range.offset + range.size)
                right = currentRange;
        }
    }
}

template <typename Size, class IdAlloc>
void Rt::Allocator::Default<Size, IdAlloc>::insertAndCoalesceUnusedRange(Range range)
{
    NeighborRange left, right;

    findFreeNeighborRanges(range, left, right);

    switch (left.exists)
    {
        case false:
        {
            switch (right.exists)
            {
                case false: {
                    unused[range.offset] = range.size;
                }
                break;

                case true: {
                    unused.erase(right.offset);
                    unused[range.offset] = range.size + right.size;
                }
                break;
            }
        }
        break;

        case true:
        {
            switch (right.exists)
            {
                case false: {
                    unused[left.offset] = left.size + range.size;
                }
                break;

                case true: {
                    unused[left.offset] = left.size + range.size + right.size;
                    unused.erase(right.offset);
                }
                break;
            }
        }
        break;
    }
}

template <typename Size, class IdAlloc>
void Rt::Allocator::Default<Size, IdAlloc>::free(Id id)
{
    auto iter = allocated.find(id);
    if (iter != allocated.end())
    {
        Range range = (*iter).second;

        allocated.erase(iter);
        allocatedSize -= range.size;

        insertAndCoalesceUnusedRange(range);
    }
    else
        error(0xB8F7031F);
}

template <typename Size, class IdAlloc>
bool Rt::Allocator::Default<Size, IdAlloc>::getAllocationInfo(Id id, Range* range)
{
    auto iter = this->allocated.find(id);
    if (iter != this->allocated.end())
    {
        if (range) *range = (*iter).second;
        return true;
    }

    return false;
}

template <typename Size, class IdAlloc>
bool Rt::Allocator::Default<Size, IdAlloc>::getAllocationInfo(Id id, Offset* offset, Size* size)
{
    Range range;
    if (getAllocationInfo(id, &range)) {
        if (offset) *offset = range.offset;
        if (size) *size = range.size;
        return true;
    }

    return false;
}

template <typename Size, class IdAlloc>
void Rt::Allocator::Default<Size, IdAlloc>::getInfo(Size* size, Size* allocatedSize)
{
    if (size) *size = this->size;
    if (allocatedSize) *allocatedSize = this->allocatedSize;
}
