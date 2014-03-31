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
            a->set(range->get().a);
            a->commit(false);

            b->set(range->get().b);
            b->commit(false);

            length->set(range->get().length());
            length->commit(false);
        }

        void invalidate() {
            if (a.get()) {
                a->invalidate();
                a->notify(this);
            }

            if (b.get()) {
                b->invalidate();
                b->notify(this);
            }

            if (length.get()) {
                length->invalidate();
                length->notify(this);
            }
        }
    };
}

#endif
