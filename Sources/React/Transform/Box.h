#ifndef header_F168564CF1ED
#define header_F168564CF1ED

namespace React
{
// Consider renaming to MakeMatrix & MakeScalar
    template <typename T>
    class Box : public Transform<Box<T>>
    {
        DF_IN(ScalarPtr<T>, input, getInput, setInput, &Box::invalidate)
        DF_OUT(MatrixPtr<T>, output, getOutput, setOutput, &Box::evaluate)

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
