#include <Runtime/Runtime.h>

//Rt::Value::Trait::Trait() : type(Type::None) {}

Rt::Value::Trait::Trait(Type type) {
    this->type = type;
}

Rt::Value::Trait::Type
Rt::Value::Trait::getType() const {
    return type;
}

void Rt::Value::Trait::traverseTree(std::function<void (std::shared_ptr<Trait>)> f) {
    f(std::shared_ptr<Trait>(this));
}

void Rt::Value::Trait::commit(bool valid, bool notify) {
    incrementVersion();
    setValidity(valid);
//    if (notify) this->notify(this);
}
