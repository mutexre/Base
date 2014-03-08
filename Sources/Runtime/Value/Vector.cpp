#include <Runtime/Runtime.h>

Rt::Value::Vector::Vector() {
    this->type = Type::Vector;
}

Rt::Value::Vector::~Vector() {}

Rt::u4 Rt::Value::Vector::getSize() {
    return this->container.size();
}

std::shared_ptr<Rt::Value::Trait>
Rt::Value::Vector::get(Rt::u4 index) {
    return this->container.at(index);
}

void Rt::Value::Vector::set(Rt::u4 index, std::shared_ptr<Trait> value) {
    this->container[index] = value;
    incrementVersion();
    notify(this);
}

void Rt::Value::Vector::traverseTree(std::function<void (std::shared_ptr<Trait>)> f) {
    for (auto& x : this->getContainer()) x->traverseTree(f);
    Trait::traverseTree(f);
}
