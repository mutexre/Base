#include <Runtime/Runtime.h>

unsigned long long int Rt::Object::allocsCount;
unsigned long long int Rt::Object::deallocsCount;

Rt::Object::Object() {
    allocsCount++;
}

Rt::Object::~Object() {
    deallocsCount++;
}

const std::string& Rt::Object::getName() const {
    return name;
}

void Rt::Object::setName(const std::string& name) {
    this->name = name;
}

const std::string& Rt::Object::getDescription() const {
    return description;
}

void Rt::Object::setDescription(const std::string& description) {
    this->description = description;
}
