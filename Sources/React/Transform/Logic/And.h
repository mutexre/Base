#ifndef header_2b01d8d4aafd
#define header_2b01d8d4aafd

namespace React
{
    namespace Logic
    {
        template <typename T>
        class And : public Transform<And<T>>
        {
            REACT_DEFINE_INPUT(ScalarPtr<T>, a, getA, setA, &And::invalidate)
            REACT_DEFINE_INPUT(ScalarPtr<T>, b, getB, setB, &And::invalidate)
            REACT_DEFINE_OUTPUT(ScalarPtr<T>, output, getOutput, setOutput, &And::evaluate)

        protected:
            void evaluate() {
//                printf("%c %c\n", a->get() ? 'y' : 'n', b->get() ? 'y' : 'n');
                output->set(a->get() && b->get());
            }

            void invalidate() {
                if (output.get()) {
                    output->invalidate();
                    output->notify(this);
                }
            }
        };
    }
}

#endif
