template <typename T>
Rt::Branching::Default<T>::Default()
{}

template <typename T>
Rt::Branching::Default<T>::Default(std::list<T> factors) {
    this->factors = factors;
}

template <typename T>
std::list<T>& Rt::Branching::Default<T>::getFactors() const {
    return factors;
}

template <typename T>
void Rt::Branching::Default<T>::setFactors(std::list<T> factors) {
    this->factors = factors;
}

template <typename T>
std::list<T> Rt::Branching::Default<T>::computePath(T address) {
    std::list<T> retval;

    if (!factors.empty())
    {
        auto factorsLength = factors.size();
        auto iter = ++factors.begin();
        auto numberOfLeafsPerBranch = std::accumulate(iter, factors.end(), 1, std::multiplies<T>());

        for (T i = 0; i < factorsLength; i++)
        {
//            printf("i=%u addr=%u numberOfLeafsPerBranch=%u *iter=%u\n", i, address, numberOfLeafsPerBranch, *iter);
            retval.push_back(address / numberOfLeafsPerBranch);
            address %= numberOfLeafsPerBranch;
            if (iter != factors.end()) {
                numberOfLeafsPerBranch = ((i < factorsLength - 1) ? (numberOfLeafsPerBranch / *iter) : 1);
                iter++;
            }
        }
    }

    return retval;
}

template <typename T>
T Rt::Branching::Default<T>::computeAddress(std::list<T> path) {
    T addr = T(0);
    auto factorsLength = factors.size();
    auto iter = ++factors.begin();
    auto numberOfLeafsPerBranch = std::accumulate(iter, factors.end(), 1, std::multiplies<T>());
    auto pathIter = path.begin();
    
    for (T i = 0; i < factorsLength; i++)
    {
        addr += numberOfLeafsPerBranch * *pathIter;
        if (iter != factors.end()) {
            numberOfLeafsPerBranch /= *iter;
            iter++;
        }
        pathIter++;
    }
    
    return addr;
}
