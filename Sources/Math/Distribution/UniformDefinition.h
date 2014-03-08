template <typename T, class RND>
Uniform<T, RND>::Uniform() : Uniform(Rt::Range<T>(T(generator.min()), T(generator.max() - generator.min()))) {}

template <typename T, class RND>
Uniform<T, RND>::Uniform(Rt::Range<T> range) {
    this->range = range;

    generatorRange = Rt::Range<typename RND::result_type>(generator.min(), generator.max() - generator.min());

    doRangesHaveEqualLength = (range.length() == generatorRange.length());
    if (doRangesHaveEqualLength)
        offset = range.a - generatorRange.a;

	generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
}

template <typename T, class RND>
T Uniform<T, RND>::sample() {
    if (doRangesHaveEqualLength)
        return T(offset + generator());
    else
        return range.a + (T(generator() - generatorRange.a) / T(generatorRange.length())) * range.length();
}

template <typename T, class RND>
Rt::Option<Rt::Range<T>> Uniform<T, RND>::getRange() {
    return Rt::Option<Rt::Range<T>>(range);
}
