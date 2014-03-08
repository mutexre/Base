template <typename Size, class IdAlloc>
void Rt::Allocator::Test<Size, IdAlloc>::printAllocator(Allocator::Default<Size, IdAlloc>& allocator)
{
    RtLog("\n");
    RTTestLog("\n");

    Size size, allocatedSize;
    allocator.getInfo(&size, &allocatedSize);
    RtLog("Size: %llu\nAllocated: %llu\n\n", size, allocatedSize);

    auto allocated = allocator.getAllocated();    
    if (!allocated.empty()) {
        RtLog("Allocated:\n");
        for (auto iter = allocated.begin(); iter != allocated.end(); iter++) {
            Id id = (*iter).first;
            auto range = (*iter).second;
            RtLog("%llu: %llu + %llu\n", id, range.offset, range.size);
        }
        RtLog("\n");
    }

    auto unused = allocator.getUnused();
    if (!unused.empty()) {
        RtLog("Unused:\n");
        for (auto iter = unused.begin(); iter != unused.end(); iter++)
            RtLog("%llu + %llu\n", (*iter).first, (*iter).second);
        RtLog("\n");
    }

    auto all = allocator.getAll();
    if (!all.empty()) {
        RtLog("Offset to size:\n");
        for (auto iter = all.begin(); iter != all.end(); iter++)
            RtLog("%llu -> %llu\n", (*iter).first, (*iter).second);
        RtLog("\n");
    }
}

template <typename Size, class IdAlloc>
int Rt::Allocator::Test<Size, IdAlloc>::deleteNonExistingId(Allocator::Default<Size, IdAlloc>& allocator, Id id)
{
    try {
        allocator.free(id);
    }
    catch (...) {
        return 0;
    }

    return 1;
}

template <typename Size, class IdAlloc>
int Rt::Allocator::Test<Size, IdAlloc>::testAllocator(Size size, u2 n, bool debug)
{
    Rt::Allocator::Default<Size, IdAlloc> allocator;
    std::unique_ptr<Id[]> ids(new Id[n]);

    if (!allocator.init(size)) {
        RTTestError("allocator.init failed\n");
        return 1;
    }

    if (debug) printAllocator(allocator);

    RtLog("***** Test alloc\n");
    for (int i = 0; i < n; i++) {
        ids[i] = allocator.alloc(size / n);
        if (ids[i] == 0) RTTestError("allocator.alloc failed\n");

        if (debug) printAllocator(allocator);
    }

    RtLog("***** Test free non-existing ids\n");
    if (deleteNonExistingId(allocator, 0)) return 1;
    if (deleteNonExistingId(allocator, 2 * n)) return 1;

    RtLog("***** Test free & alloc\n");
    allocator.free(ids[0]);
    if (debug) printAllocator(allocator);

    ids[0] = allocator.alloc(2 * size / n);
    if (ids[0] != 0) RTTestError("allocator.alloc failed\n");
    if (debug) printAllocator(allocator);

    ids[0] = allocator.alloc(size / n);
    if (ids[0] == 0) RTTestError("allocator.alloc failed\n");
    if (debug) printAllocator(allocator);

    RtLog("***** Test free\n");
    for (int i = 0; i < n; i++) {
        auto id = ids[i];
        if (id != 0) {
            allocator.free(id);
            if (debug) printAllocator(allocator);
        }
    }

    return 0;
}

template <typename Size, class IdAlloc>
int Rt::Allocator::Test<Size, IdAlloc>::testRandomAllocations(Size min, Size max, u2 n)
{
    Rt::Allocator::Default<Size, IdAlloc> allocator;
    std::vector<Size> sizes(n);
    std::vector<Id> ids;
    Size wholeSize = 0;

    RtLog("***** Test random allocs\n");

    Algo::Vector::randomize(sizes.begin(), sizes.end(), min, max);
    for (auto s : sizes) wholeSize += s;

    RTTestLog("Whole size is %llu bytes\n", wholeSize);

    if (!allocator.init(wholeSize)) {
        RTTestError("allocator.init failed\n");
        return 1;
    }

    for (auto s : sizes) {
        auto id = allocator.alloc(s);
        if (id == 0) {
            RTTestError("allocator.alloc failed\n");
            return 1;
        }
        ids.push_back(id);
    }

    std::random_shuffle(ids.begin(), ids.end());

    for (auto id : ids) {
        try {
            allocator.free(id);
        }
        catch (...) {
            RTTestError("allocator.free failed\n");
            return 1;
        }
    }

    return 0;
}

template <typename Size, class IdAlloc>
int Rt::Allocator::Test<Size, IdAlloc>::test()
{
    int result;

    result = testAllocator(128, 8, false);
    if (result) return result;

    result = testRandomAllocations(0, 1000, 2000);
    if (result) return result;

    return 0;
}
