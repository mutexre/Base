#ifndef header_9094F96E38CD
#define header_9094F96E38CD

namespace React
{
    template <typename T>
    class RangeInfo : public Transform<RangeInfo<T>>
    {
        REACT_DEFINE_INPUT(ScalarPtr<Rt::Range<T>>, range, getRange, setRange, &RangeInfo::invalidate)
        REACT_DEFINE_OUTPUT(ScalarPtr<T>, a, getA, setA, &RangeInfo::evaluate)
        REACT_DEFINE_OUTPUT(ScalarPtr<T>, b, getB, setB, &RangeInfo::evaluate)
        REACT_DEFINE_OUTPUT(ScalarPtr<T>, length, getLength, setLength, &RangeInfo::evaluate)

    private:
        void evaluate() {
            auto& rangeVal = range->get();

            if (a.get()) {
                a->set(rangeVal.a);
                a->commit(false);
            }

            if (b.get()) {
                b->set(rangeVal.b);
                b->commit(false);
            }

            if (length.get()) {
                length->set(rangeVal.length());
                length->commit(false);
            }
        }

        void invalidate() {
            if (a.get())
                a->invalidate();

            if (b.get())
                b->invalidate();

            if (length.get())
                length->invalidate();
        }
    };
}

#endif
