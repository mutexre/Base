template <typename Size, class IdAlloc>
int Rt::Memory::Test<Size, IdAlloc>::testManager(Trait<Size, Id>* manager)
{
    typename IdAlloc::IdType id = manager->alloc(CommonRequirements<Size>::pack(100));
    if (id == 0) return 1;

    void* ptr = manager->map(id);
    if (!ptr)
    {
        RTTestError("map failed\n");
        return 1;
    }

    memset(ptr, 'T', 100);
    if (debug) Rt::dump(ptr, 100);

    manager->unmap(id);

    try {
        manager->free(id);
    }
    catch (...) {
        RTTestError("free failed\n");
        return 1;
    }

    return 0;
}

template <typename Size, class IdAlloc>
int Rt::Memory::Test<Size, IdAlloc>::testMallocManager()
{
    Rt::Memory::Malloc<Size, IdAlloc> manager;
    int result;

    result = testManager(&manager);
    if (result != 0) return result;

    return 0;
}

template <typename Size, class IdAlloc>
int Rt::Memory::Test<Size, IdAlloc>::testBufferManager()
{
    Rt::Memory::Buffer<Size, IdAlloc> manager(10000);
    int result;

    result = testManager(&manager);
    if (result != 0) return result;

    return 0;
}

template <typename Size, class IdAlloc>
int Rt::Memory::Test<Size, IdAlloc>::testMultiBuffer()
{
    Rt::Memory::Multibuffer::Default<Size, IdAlloc> manager(512 * 1024);
    std::forward_list<typename IdAlloc::IdType> ids;

    for (auto i = 0; i < 10; i++) {
        auto id = manager.alloc(CommonRequirements<Size>::pack(129 * 1024));
        if (id == 0) return 1;

        ids.push_front(id);

        void* ptr = manager.map(id);
        if (!ptr) {
            RTTestError("map failed\n");
            return 1;
        }

        memset(ptr, 'T', 100);
        if (debug) Rt::dump(ptr, 100);

        manager.unmap(id);
    }

    for (auto id : ids) {
        try {
            manager.free(id);
        }
        catch (...) {
            RTTestError("free failed\n");
            return 1;
        }
    }

    return 0;
}

template <typename Size, class IdAlloc>
int Rt::Memory::Test<Size, IdAlloc>::testManagers()
{
    int result;

    result = testMallocManager();
    if (result != 0)
    {
        RTTestLog("test basic manager -> %d\n", result);
        return result;
    }

    result = testBufferManager();
    if (result != 0)
    {
        RTTestLog("test buffer manager -> %d\n", result);
        return result;
    }

    result = testMultiBuffer();
    if (result != 0)
    {
        RTTestLog("test multibuffer manager -> %d\n", result);
        return result;
    }

    return 0;
}

template <typename Size, class IdAlloc>
int Rt::Memory::Test<Size, IdAlloc>::test()
{
    int result;

    result = testManagers();
    if (result) return result;

    return 0;
}
