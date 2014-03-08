template <class A>
void ReadWrite<A>::read(Id ID, Offset offset, Size size, void* ptr) {
    auto iter = this->ids2allocations.find(ID);
    if (iter != this->ids2allocations.end()) {
        auto& allocationInfo = (*iter).second;
        allocationInfo.first->read(allocationInfo.second, offset, size, ptr);
    }
    else
        error(0x742DE14B);
}

template <class A>
void ReadWrite<A>::write(Id ID, Offset offset, Size size, const void* ptr) {
    auto iter = this->ids2allocations.find(ID);
    if (iter != this->ids2allocations.end()) {
        auto& allocationInfo = (*iter).second;
        allocationInfo.first->write(allocationInfo.second, offset, size, ptr);
    }
    else
        error(0x3770546E);
}
