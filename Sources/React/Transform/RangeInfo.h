#ifndef header_9094F96E38CD
#define header_9094F96E38CD

namespace React
{
    template <typename T>
    class RangeInfo : public Transform<RangeInfo<T>>
    {
        DF_IN(ScalarPtr<Rt::Range<T>>, range, getRange, setRange, &RangeInfo::invalidate)
        DF_OUT(ScalarPtr<T>, a, getA, setA, &RangeInfo::evaluate)
        DF_OUT(ScalarPtr<T>, b, getB, setB, &RangeInfo::evaluate)
        DF_OUT(ScalarPtr<T>, length, getLength, setLength, &RangeInfo::evaluate)

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
