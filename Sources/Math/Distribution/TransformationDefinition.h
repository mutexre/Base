template <typename T1, typename T2>
Transformation<T1, T2>::Transformation(Trait<T1>* distr, std::function<T2(T1)> f) : Transformation() {
    this->distr = distr;
    this->f = f;
}

template <typename T1, typename T2>
bool Transformation<T1, T2>::isMonotonic() const {
    return isMonotonic;
}

template <typename T1, typename T2>
void Transformation<T1, T2>::setMonotonicity(bool value) {
    monotonic = value;
}

template <typename T1, typename T2>
T2 Transformation<T1, T2>::sample() {
    return f(distr->sample());
}

template <typename T1, typename T2>
Rt::Option<Rt::Range<T2>>
Transformation<T1, T2>::getRange()
{
    if (isMonotonic()) {
        auto distrRange = distr->getRange();
        if (distrRange.defined)
            return Rt::Option<Rt::Range<T2>>(f(distrRange.a), f(distrRange.b) - f(distrRange.a));
        else
            return Rt::Option<Rt::Range<T2>>();
    }
    else
        return Rt::Option<Rt::Range<T2>>();
}
