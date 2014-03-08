template <typename T>
Rt::Option<T>
Rt::Value::Map::getScalar(PropertyName property) const
{
    Option<T> value;

    auto optionalValue = get(property);
    if (optionalValue.defined) {
        switch (optionalValue.value->getType()) {
            case Value::Trait::Type::Scalar: {
                auto propertyValue = dynamic_cast<const Value::Scalar<T>*>(optionalValue.value.get());
                if (!propertyValue) error(0xDAB882FD);

                value.define(propertyValue->get());
            }
            break;

            default: error(0x1A501361);
        }
    }

    return value;
}

template <typename T>
void Rt::Value::Map::setScalar(PropertyName property, Option<T> optionalValue)
{
    if (optionalValue.defined) {
        set(property, std::make_shared<Value::Scalar<T>>(optionalValue.value));
    }
    else {
        if (getCount(property) > 0)
            erase(property);
    }
}

template <typename T>
void Rt::Value::Map::setScalar(PropertyName property, T value) {
    set(property, std::make_shared<Value::Scalar<T>>(value));
}
