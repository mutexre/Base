template <class Iterator, typename T>
void Rt::Algo::Vector::fillWithIncreasingSequence(Iterator begin, Iterator end, T min, T interval)
{
    auto currentValue = min;
    for (auto iter = begin; iter != end; iter++) {
        *iter = currentValue;
        currentValue += interval;
    }
}

template <class Iterator, typename T>
void Rt::Algo::Vector::randomize(Iterator begin, Iterator end, T min, T max)
{
    for (auto iter = begin; iter != end; iter++)
        *iter = min + rand() % (max - min);
}

template <class Iterator, typename T>
void Rt::Algo::Vector::randomizeWithUniqueValues(Iterator begin, Iterator end, T min, T max)
{
    std::set<T> set;

    for (auto iter = begin; iter != end; iter++) {
        T value;

        do { value = min + rand() % (max - min); }
        while (!set.insert(value).second);

        *iter = value;
    }
}
