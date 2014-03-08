#include <Runtime/Runtime.h>

Rt::Value::Map::Map() {
    this->type = Type::Map;
}

Rt::Value::Map::Map(const Map& that) {
    container = that.container;
}

Rt::Value::Map::~Map() {}

Rt::Value::Map
Rt::Value::Map::operator+(const Map& that) const {
    Map retval;

    retval.container = that.container;
    retval.container.insert(this->container.begin(), this->container.end());

    return retval;
}

Rt::Value::Map&
Rt::Value::Map::operator+=(const Map& that) {
    this->container.insert(that.container.begin(), that.container.end());
    return *this;
}

Rt::u4 Rt::Value::Map::getCount(PropertyName property) const {
    return this->container.count(std::string(property));
}

Rt::Option<std::shared_ptr<Rt::Value::Trait>>
Rt::Value::Map::get(PropertyName property) const {
    auto iter = this->container.find(std::string(property));
    return (iter != this->container.end()) ? Option<std::shared_ptr<Trait>>((*iter).second) : Option<std::shared_ptr<Trait>>();
}

void Rt::Value::Map::set(PropertyName property, std::shared_ptr<Trait> value) {
    this->container[std::string(property)] = value;
    incrementVersion();
    notify(this);
}

void Rt::Value::Map::erase(PropertyName property) {
    this->container.erase(std::string(property));
    incrementVersion();
    notify(this);
}

void Rt::Value::Map::traverseTree(std::function<void (std::shared_ptr<Trait>)> f) {
    for (auto& x : this->getContainer()) x.second->traverseTree(f);
    Trait::traverseTree(f);
}
