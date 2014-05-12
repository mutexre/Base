#ifndef header_58E27E4DB3E4
#define header_58E27E4DB3E4

#define REACT_DEFINE_GETTER(type, var, name)\
    const type& name() const {\
        return var;\
    }

#define REACT_DEFINE_INPUT_SETTER(type, var, name, invalidator)\
    void name(type value) {\
        auto previousVar = this->var;\
        auto iter = this->invalidators.find(previousVar.get());\
        if (iter != this->invalidators.end())\
            this->invalidators.erase(iter);\
        this->invalidators[value.get()] = invalidator; \
        this->var = value;\
        connections_##var = this->observe(value.get());\
        (this->*invalidator)();\
    }

#define REACT_DEFINE_INPUT(type, var, getter, setter, invalidator)\
protected:\
    type var;\
    React::Observable<2>::Connection connections_##var;\
public:\
    REACT_DEFINE_GETTER(type, var, getter)\
    REACT_DEFINE_INPUT_SETTER(type, var, setter, invalidator)

#define REACT_DEFINE_OUTPUT_SETTER(type, var, name, evalFunc)\
    void name(type value) {\
        auto previousVar = this->var;\
        auto iter = this->evaluators.find(previousVar.get());\
        if (iter != this->evaluators.end())\
            this->evaluators.erase(iter);\
        this->evaluators[value.get()] = evalFunc;\
        this->var = value;\
        value->setProvider(this->shared_from_this());\
        value->notify(value.get());\
    }

#define REACT_DEFINE_OUTPUT(type, var, getter, setter, evalFunc)\
protected:\
    type var;\
public:\
    REACT_DEFINE_GETTER(type, var, getter)\
    REACT_DEFINE_OUTPUT_SETTER(type, var, setter, evalFunc)

#define REACT_DEFINE_VECTOR_GETTER(type, var, name)\
    const type& name(Rt::u2 index) const {\
        return var[index];\
    }

#define REACT_DEFINE_INPUT_VECTOR_SETTER(type, var, name, callback)\
    void name(Rt::u2 index, type value) {\
        auto previousVar = this->var[index];\
        auto iter = this->invalidators.find(previousVar.get());\
        if (iter != this->invalidators.end())\
            this->invalidators.erase(iter);\
        this->invalidators[value.get()] = callback;\
        this->var[index] = value;\
        connections_##var[index] = this->observe(value.get());\
        (this->*callback)();\
    }

#define REACT_DEFINE_INPUT_VECTOR_ADDER(type, var, name, callback)\
    void name(type value) {\
        this->invalidators[value.get()] = callback;\
        this->var.push_back(value);\
        connections_##var.push_back(this->observe(value.get()));\
        (this->*callback)();\
    }

#define REACT_DEFINE_VECTOR_INPUT(type, var, getter, setter, adder, callback)\
protected:\
    std::vector<type> var;\
    std::vector<React::Observable<2>::Connection> connections_##var;\
public:\
    REACT_DEFINE_VECTOR_GETTER(type, var, getter)\
    REACT_DEFINE_INPUT_VECTOR_SETTER(type, var, setter, callback)\
    REACT_DEFINE_INPUT_VECTOR_ADDER(type, var, adder, callback)

#define REACT_DEFINE_OUTPUT_VECTOR_SETTER(type, var, name, evalFunc)\
    void name(Rt::u2 index, type value) {\
        auto previousVar = this->var[index];\
        auto iter = this->evaluators.find(previousVar.get());\
        if (iter != this->evaluators.end())\
            this->evaluators.erase(iter);\
        this->evaluators[value.get()] = evalFunc;\
        this->var[index] = value;\
        value->setProvider(this->shared_from_this());\
        value->notify(value.get());\
    }

#define REACT_DEFINE_OUTPUT_VECTOR_ADDER(type, var, name, evalFunc)\
    void name(type value) {\
        this->evaluators[value.get()] = evalFunc;\
        this->var.push_back(value);\
        value->setProvider(this->shared_from_this());\
        value->notify(value.get());\
    }

#define REACT_DEFINE_VECTOR_OUTPUT(type, var, getter, setter, adder, evalFunc)\
protected:\
    std::vector<type> var;\
public:\
    REACT_DEFINE_VECTOR_GETTER(type, var, getter)\
    REACT_DEFINE_OUTPUT_VECTOR_SETTER(type, var, setter)\
    REACT_DEFINE_OUTPUT_VECTOR_ADDER(type, var, adder)

#endif
