#ifndef header_aef842abc6e4
#define header_aef842abc6e4

namespace React
{
    template <typename T>
    class MultiplyByScalar : public Transform<MultiplyByScalar<T>>
    {
        REACT_DEFINE_INPUT(ScalarPtr<T>, input, getInput, setInput, &MultiplyByScalar::invalidate)
        REACT_DEFINE_OUTPUT(ScalarPtr<T>, output, getOutput, setOutput, &MultiplyByScalar::evaluate)

    protected:
        T multiplier;

    protected:
        void evaluate() {
            this->output->set(multiplier * input->get());
            this->output->commit(false);
        }

        void invalidate() {
            if (output.get()) {
                output->invalidate();
                output->notify(this);
            }
        }

    public:
        MultiplyByScalar(T multiplier) {
            this->multiplier = multiplier;
        }
    };
}

#endif
