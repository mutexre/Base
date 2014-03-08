#include <uuid/uuid.h>
#include <Runtime/Runtime.h>

Rt::Value::Uuid::Uuid() {}

Rt::Value::Uuid::Uuid(Rt::uuid value) : Trait(Type::Uuid) {
    uuid_copy(this->value, value);
}

void Rt::Value::Uuid::get(Rt::uuid& value) {
    uuid_copy(this->value, value);
}

void Rt::Value::Uuid::set(Rt::uuid value) {
    uuid_copy(this->value, value);
    incrementVersion();
    notify(this);
}

void Rt::Value::Uuid::generate() {
    uuid_generate(value);
    incrementVersion();
    notify(this);
}
