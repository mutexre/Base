template <class A>
Value::Map Info<A>::getAllocationInfo(Id id) {
    Value::Map info;

    auto iter = this->ids2allocations.find(id);
    if (iter != this->ids2allocations.end()) {
        auto& allocator = (*iter).second.first;
        auto allocationId = (*iter).second.second;

        auto allocationInfo = allocator->getAllocationInfo(allocationId);
        info.set("allocation", std::make_shared<Value::Map>(allocationInfo));

        auto allocatorInfo = allocator->getInfo();
        info.set("allocator", std::make_shared<Value::Map>(allocatorInfo));
    }
    else
        error(0x167BCD6F);

    return info;
}
