#ifndef header_8f8fffc293b9
#define header_8f8fffc293b9

namespace React
{
    template <typename T>
    class Negate : public Transform<Negate<T>>
    {
        REACT_DEFINE_INPUT(ScalarPtr<T>, input, getInput, setInput, &Negate::invalidate)
        REACT_DEFINE_OUTPUT(ScalarPtr<T>, output, getOutput, setOutput, &Negate::evaluate)

    protected:
        void evaluate() {
            this->output->set((-1) * input->get());
            this->output->commit(false);
        }

        void invalidate() {
            if (output.get()) {
                output->invalidate();
                output->notify(this);
            }
        }
    };
}

#endif
