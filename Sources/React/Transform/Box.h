#ifndef header_F168564CF1ED
#define header_F168564CF1ED

namespace React
{
    template <typename T>
    class Box : public Transform<Box<T>>
    {
        REACT_DEFINE_INPUT(ScalarPtr<T>, input, getInput, setInput, &Box::invalidate)
        REACT_DEFINE_OUTPUT(MatrixPtr<T>, output, getOutput, setOutput, &Box::evaluate)

    protected:
        void evaluate() {
            this->output->currentValue().set(0, input->get());
            this->output->commit(false);
        }

        void invalidate() {
            if (output.get())
                output->invalidate();
        }
    };
}

#endif
