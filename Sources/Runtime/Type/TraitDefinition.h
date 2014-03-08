template <typename T, typename I>
Rt::Type::Trait<T, I>::~Trait() {}

template <typename T, typename I>
T Rt::Type::Trait<T, I>::round(T x, T rounding) {
    return rounding * ((x - T(1)) / rounding + T(1));
}

template <typename T, typename I>
void Rt::Type::Trait<T, I>::copyAttributesTo(Trait<T, I>* that) {
    that->name = name;
    that->rounding = rounding;
}

template <typename T, typename I>
T Rt::Type::Trait<T, I>::getRoundedSize() {
    auto size = getSize();
    if (rounding.defined) return round(size, rounding.value);
    else return size;
}

template <typename T, typename I>
Rt::Option<std::string> Rt::Type::Trait<T, I>::getName() const {
    return name;
}

template <typename T, typename I>
void Rt::Type::Trait<T, I>::setName(Option<std::string> name) {
    this->name = name;
}

template <typename T, typename I>
Rt::Option<T> Rt::Type::Trait<T, I>::getRounding() const {
    return rounding;
}

template <typename T, typename I>
void Rt::Type::Trait<T, I>::setRounding(Option<T> rounding) {
    this->rounding = rounding;
}

template <typename T, typename I>
void Rt::Type::Trait<T, I>::setRoundingRecursively(Option<T> rounding) {
    setRounding(rounding);
}

template <typename T, typename I>
Rt::Option<Rt::Type::Trait<T, I>*> Rt::Type::Trait<T, I>::getParent() const {
    return parent;
}

template <typename T, typename I>
void Rt::Type::Trait<T, I>::setParent(Option<Trait*> parent) {
    if (!this->parent.defined) this->parent = parent;
    else Rt::error(0x0B8F3F52);
}

template <typename T, typename I>
typename Rt::Type::Trait<T,I>::Kind Rt::Type::Trait<T, I>::getKind() const {
    return kind;
}

template <typename T, typename I>
void* Rt::Type::Trait<T, I>::getUserData() const {
    return userData;
}

template <typename T, typename I>
void Rt::Type::Trait<T, I>::setUserData(void* data) {
    this->userData = data;
}

template <typename T, typename I>
bool Rt::Type::Trait<T, I>::execAppropriateFunc(std::function<bool (Atom<T, I>*)> atomOp,
                                                std::function<bool (Struct<T, I>*)> structOp,
                                                std::function<bool (Matrix<T, I>*)> matrixOp)
{
    switch (kind) {
        case Kind::Atom: return atomOp((Atom<T, I>*)this);
        case Kind::Struct: return structOp((Struct<T, I>*)this);
        case Kind::Matrix: return matrixOp((Matrix<T, I>*)this);
    }
}

template <typename T, typename I>
void Rt::Type::Trait<T, I>::traverseAncestors(std::function<bool (Trait*)> f) {
    Trait* current = this;
    while (1) {
        if (current->parent.defined) {
            if (!f(current = current->parent.value)) break;
        }
        else
            break;
    }
}

template <typename T, typename I>
void Rt::Type::Trait<T, I>::traverseAncestors(std::function<bool (Struct<T, I>*)> structOp,
                                              std::function<bool (Matrix<T, I>*)> matrixOp) {
    Trait* current = this;
    while (1) {
        if (current->parent.defined) {
            bool result;

            current = current->parent.value;
            switch (current->kind) {
                case Kind::Struct: result = structOp((Struct<T, I>*)current); break;
                case Kind::Matrix: result = matrixOp((Matrix<T, I>*)current); break;
                case Kind::Atom: Rt::error(0x09385C04); break;
            }

            if (!result) break;
//            if (!(current = current->parent.value)->execAppropriateFunc(0, structOp, matrixOp)) break;
        }
        else
            break;
    }
}

template <typename T, typename I>
void Rt::Type::Trait<T, I>::traverseTree(std::function<void (Trait*)> f) {
/*
        if (name.defined)
            printf("name=%s\n", name.value.c_str());
        else
            printf("no name\n");
*/
    f(this);
}

template <typename T, typename I>
void Rt::Type::Trait<T, I>::updateRecursively() {
    traverseTree([](Trait* type) {
        if (type->getKind() == Kind::Struct) {
            Struct<T, I>* s = (Struct<T, I>*)type;
            auto numberOfMembers = s->getMembers().size();
            std::vector<T> sizes(numberOfMembers);
            std::vector<T> offsets(numberOfMembers);

            for (auto& m : s->getMembers())
                sizes[m.second.index] = m.first->getRoundedSize();

            T offset = 0;
            for (unsigned int i = 0; i < numberOfMembers; i++) {
                offsets[i] = offset;
                offset += sizes[i];
            }

            for (auto& m : s->getMembers())
                m.second.offset = offsets[m.second.index];
        }
    });
}

template <typename T, typename I>
std::list<Rt::Type::Trait<T, I>*> Rt::Type::Trait<T, I>::getAncestors() {
    std::list<Trait*> retval;
    traverseAncestors([&retval](Trait<T, I>* t) -> bool {
        retval.push_front(t);
        return true;
    });
    return retval;
}

template <typename T, typename I>
I Rt::Type::Trait<T, I>::getNumberOfOccurences() {
    I numberOfOccurences = 1;
    traverseAncestors(
        [](Struct<T, I>*) -> bool { return true; },
        [&numberOfOccurences](Matrix<T, I>* t) -> bool {
            numberOfOccurences *= t->getNumberOfElements();
            printf("x=%u\n", t->getNumberOfElements());
            return true;
        });
    
    return numberOfOccurences;
}

template <typename T, typename I>
std::list<I> Rt::Type::Trait<T, I>::getBranchingFactors() {
    std::list<I> factors;
    traverseAncestors(
        [](Trait*) -> bool { return true; },
        [&factors](Matrix<T, I>* t) -> bool {
            factors.push_front(t->getNumberOfElements());
            return true;
        });
    return factors;
}

template <typename T, typename I>
T Rt::Type::Trait<T, I>::offsetOfOccurenceWithIndex(I index) {
    Branching::Default<I> b(getBranchingFactors());
    std::list<I> path = b.computePath(index);
    std::list<Trait*> ancestors = getAncestors();
    auto ancestorIter = ancestors.begin();
    auto ancestorsSize = ancestors.size();
    auto pathIter = path.begin();
    T offset = 0;

    for (I i = 0; i < ancestorsSize; i++) {
        Trait* current = *ancestorIter;

        switch (current->kind)
        {
            case Kind::Struct: {
                Trait* member;
                if (i < ancestorsSize - 1) {
                    auto nextAncestorIter = ancestorIter; nextAncestorIter++;
                    member = *nextAncestorIter;
                }
                else
                    member = this;

                offset += (((Struct<T, I>*)current)->getMembers())[member].offset;
            }
            break;

            case Kind::Matrix: {
                offset += (*pathIter) * ((Matrix<T, I>*)current)->getRoundedSize();
                pathIter++;
            }
            break;

            default: break;
        }

        ancestorIter++;
    }

    return offset;
}

template <typename T, typename I>
Rt::Option<std::pair<T, T>> Rt::Type::Trait<T, I>::getStrideAndOffset() {
    T offset = 0;
    Option<std::pair<T, T>> retval;
    auto p = this;

    traverseAncestors(
        [&](Struct<T, I>* t) -> bool {
            offset += t->getMembers()[p].offset;
            p = t;
            return true;
        },
        [&](Matrix<T, I>* t) -> bool {
            if (retval.defined) {
                retval.defined = false;
                return false;
            }

            retval.define(std::pair<T, T>(t->getNestedType()->getRoundedSize(), offset));
            p = t;

            return true;
        }
    );
    
    return retval;
}

template <typename T, typename I>
Rt::Type::Matrix<T, I>* Rt::Type::Trait<T, I>::operator*(I n) {
    return new Matrix<T, I>(this, n);
}
