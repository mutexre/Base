template <typename Id>
bool Rt::IDAllocator::Default<Id>::get(Id* id)
{
    if (current <= this->maxId)
        *id = current++;
    else
        return false;

    return true;
}

template <typename Id>
void Rt::IDAllocator::Default<Id>::put(Id)
{}
