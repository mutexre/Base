template <typename Id>
Alloc<Id>::Alloc(Value::Map defaultRequirements) {
    setDefaultRequirements(defaultRequirements);
}

template <typename Id>
Value::Map Alloc<Id>::getDefaultRequirements() {
    return defaultRequirements;
}

template <typename Id>
void Alloc<Id>::setDefaultRequirements(Value::Map r) {
    this->defaultRequirements = r;
}

template <typename Id>
Id Alloc<Id>::alloc() {
    return alloc(Value::Map());
}

template <typename Id>
Id Alloc<Id>::alloc(Value::Map requirements) {
    return inheritedAlloc(getDefaultRequirements() + requirements);
}
