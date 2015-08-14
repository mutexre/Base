#ifndef header_aef842abc6e4
#define header_aef842abc6e4

namespace React
{
    template <typename T>
    class MultiplyByScalar : public Transform<MultiplyByScalar<T>>
    {
        DF_IN(ScalarPtr<T>, input, getInput, setInput, &MultiplyByScalar::invalidate)
        DF_OUT(ScalarPtr<T>, output, getOutput, setOutput, &MultiplyByScalar::evaluate)

    protected:
        T multiplier;

    protected:
        void evaluate() {
            this->output->set(multiplier * input->get());
            this->output->commit(false);
        }

        void invalidate() {
            if (output.get())
                output->invalidate();
        }

    public:
        MultiplyByScalar(T multiplier) {
            this->multiplier = multiplier;
        }
    };
}

#endif
