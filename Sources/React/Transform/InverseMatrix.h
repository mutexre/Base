#ifndef header_ae91733f9daa
#define header_ae91733f9daa

namespace React
{
    template <typename T>
    class InverseMatrix : public Transform<InverseMatrix<T>>
    {
        REACT_DEFINE_INPUT(MatrixPtr<T>, input, getInput, setInput, &InverseMatrix::invalidate)
        REACT_DEFINE_OUTPUT(MatrixPtr<T>, output, getOutput, setOutput, &InverseMatrix::evaluate)

    protected:
        void evaluate() {
            auto result = Math::Matrix<T>::getInversed(input->get());
            if (result.defined) {
                this->output->set(result.get());
                this->output->commit(false);
            }
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
