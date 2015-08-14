#ifndef header_ae91733f9daa
#define header_ae91733f9daa

namespace React
{
    template <typename T>
    class InverseMatrix : public Transform<InverseMatrix<T>>
    {
        DF_IN(MatrixPtr<T>, input, getInput, setInput, &InverseMatrix::invalidate)
        DF_OUT(MatrixPtr<T>, output, getOutput, setOutput, &InverseMatrix::evaluate)

    protected:
        void evaluate() {
            auto result = Math::Matrix<T>::getInversed(input->get());
            if (result.defined) {
                this->output->set(result.get());
                this->output->commit(false);
            }
        }

        void invalidate() {
            if (output.get())
                output->invalidate();
        }
    };
}

#endif
