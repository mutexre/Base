template <class T>
void* Map<T>::map(Id ID) {
    auto iter = this->ids2allocations.find(ID);
    if (iter != this->ids2allocations.end()) {
        auto& allocationInfo = (*iter).second;
        return allocationInfo.first->map(allocationInfo.second);
    }
    else
        error(0xD6AD2F72);

    return 0;
}

template <class T>
void Map<T>::unmap(Id ID) {
    auto iter = this->ids2allocations.find(ID);
    if (iter != this->ids2allocations.end()) {
        auto& allocationInfo = (*iter).second;
        allocationInfo.first->unmap(allocationInfo.second);
    }
    else
        error(0xF2E3CD6A);
}
