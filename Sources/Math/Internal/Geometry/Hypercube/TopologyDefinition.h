template <typename D, typename I>
Topology<D, I>::Id::Id(D dim, I mask, I value) {
    this->dim = dim;
    this->mask = mask;
    this->value = value;
}

template <typename D, typename I>
bool Topology<D, I>::Id::operator<(const Id& that) const {
    if (mask == that.mask)
        return value < that.value;
    return mask < that.mask;
}

template <typename D, typename I>
bool Topology<D, I>::Id::operator>(const Id& that) const {
    return !operator<(that);
}
/*
template <typename D, typename I>
bool Topology<D, I>::Id::operator<=(const Id& that) {
    return !operator>(that);
}

template <typename D, typename I>
bool Topology<D, I>::Id::operator>=(const Id& that) {
    return !operator<(that);
}
*/
template <typename D, typename I>
I Topology<D, I>::getCount(D boundingDim, D dim) {
    return Math::calcNumberOfCombinations<D, I>(boundingDim, boundingDim - dim) * Math::powOf2<D, I>(boundingDim - dim);
}

template <typename D, typename I>
I Topology<D, I>::getCount(D boundingDim, D dim, D elementsDim)
{
    if (dim > elementsDim)
        return getCount(dim, elementsDim);

    if (dim < elementsDim)
        return Math::calcNumberOfCombinations<D, I>(boundingDim - dim, boundingDim - elementsDim);

    return 1;
}

template <typename D, typename I>
I Topology<D, I>::getCount(D boundingDim, Id id, D elementsDim) {
    return getCount(boundingDim, id.dim, elementsDim);
}

template <typename D, typename I>
std::vector<typename Topology<D, I>::Id>
Topology<D, I>::getElements(D boundingDim, D dim)
{
    std::vector<Id> retval;
    I mask = (I(1) << (boundingDim - dim)) - 1;
    I numberOfCombinations = Math::calcNumberOfCombinations<D, I>(boundingDim, boundingDim - dim);
    I numberOfElementsInPermutation = Math::powOf2<D, I>(boundingDim - dim);

    for (I i = 0; i < numberOfCombinations; i++)
    {
        for (I j = 0; j < numberOfElementsInPermutation; j++)
            retval.push_back(Id(dim, mask, Rt::distributeBits(j, mask, boundingDim - dim)));
        mask = Math::nextPermutationInLexicographicalOrder(mask);
    }

    return retval;
}

template <typename D, typename I>
std::vector<typename Topology<D, I>::Id>
Topology<D, I>::getElements(D boundingDim, Id id, D elementsDim)
{
    std::vector<Id> retval;

    if (id.dim > elementsDim) {
        std::vector<Id> retval;
        I mask = (I(1) << (id.dim - elementsDim)) - 1;
        I numberOfCombinations = Math::calcNumberOfCombinations<D, I>(id.dim, elementsDim);
        I numberOfElementsInPermutation = Math::powOf2<D, I>(id.dim - elementsDim);

        for (I i = 0; i < numberOfCombinations; i++) {
            I m = Rt::distributeBits(mask, ~id.mask, id.dim);
            for (I j = 0; j < numberOfElementsInPermutation; j++)
                retval.push_back(Id(elementsDim, id.mask | m, id.value | Rt::distributeBits(j, m, id.dim - elementsDim)));
            mask = Math::nextPermutationInLexicographicalOrder(mask);
        }

        return retval;
    }

    if (id.dim < elementsDim) {
        std::vector<Id> retval;
        I mask = (I(1) << (boundingDim - elementsDim)) - 1;
        I numberOfCombinations = Math::calcNumberOfCombinations<D, I>(boundingDim - id.dim, boundingDim - elementsDim);

        for (I i = 0; i < numberOfCombinations; i++) {
            I elementMask = Rt::distributeBits(mask, id.mask, boundingDim - id.dim);
            retval.push_back(Id(elementsDim, elementMask, id.value & elementMask));
            mask = Math::nextPermutationInLexicographicalOrder(mask);
        }

        return retval;
    }

    retval.push_back(id);

    return retval;
}
