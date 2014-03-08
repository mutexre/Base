#if defined _WIN32 || defined _WIN64

Rt::u4 __inline ctz(Rt::u4 x) {
   unsigned long r = 0;
   _BitScanForward(&r, x);
   return r;
}

#endif

template <typename N, typename T>
T powOf2(N n) { return T(1) << n; }

template <typename N, typename T>
T calcNumberOfCombinations(N numberOfSlots, N numberOfThings) {
    T retval = 1;

    if (numberOfSlots > 0 && numberOfSlots != numberOfThings)
    {
        for (N i = (numberOfSlots - numberOfThings + 1); i <= numberOfSlots; i++)
            retval *= i;

        for (N i = 2; i <= numberOfThings; i++)
            retval /= i;
    }

    return retval;
}

template <typename T>
T nextPermutationInLexicographicalOrder(T permutation)
{
    // t gets v's least significant 0 bits set to 1
    T t = permutation | (permutation - 1);

    // Next set to 1 the most significant bit to change, 
    // set to 0 the least significant ones, and add the necessary 1 bits.
#ifdef _MSC_VER
    return (t + 1) | (((~t & -~t) - 1) >> (ctz(permutation) + 1));
#else
    return (t + 1) | (((~t & -~t) - 1) >> (std::__ctz(permutation) + 1));
#endif
}

template <typename T, typename D, typename I>
std::vector<T> calcCenterOfMass(const std::vector<T>& vec, D dim, I count) {
    std::vector<T> cm(dim, T(0));

    for (auto i = 0; i < count; i++)
        for (auto j = 0; j < dim; j++)
            cm[j] += vec[i * dim + j];

    auto count_inv = T(1) / T(count);
    for (auto& x : cm) x *= count_inv;

    return cm;
}

template <typename T, typename D, typename I>
T calcMaxDistFromPoint(const std::vector<T>& vec, D dim, I count, const std::vector<T>& point) {
    T maxDist = 0;

    for (I i = 0; i < count; i++) {
        T dist = 0;

        for (D j = 0; j < dim; j++) {
            auto x = vec[i * dim + j] - point[j];
            dist += x * x;
        }
        dist = std::sqrt(dist);

        if (dist > maxDist) maxDist = dist;
    }

    return maxDist;
}

template <typename T>
void normalize(std::vector<T>& vec, T value) {
    auto sum = std::accumulate(vec.begin(), vec.end(), T(0), [](T x, T y) -> T {
        return std::abs(x) + std::abs(y);
    });
    
    auto mean = sum / vec.size();

    auto coeff = value / mean;
    for (auto iter = vec.begin(); iter != vec.end(); iter++)
        *iter *= coeff;
}
