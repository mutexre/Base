#ifndef header_9307debb5fe5
#define header_9307debb5fe5

namespace React
{
    template <typename T>
    class InverseTranspose : public Transform<InverseTranspose<T>>
    {
        REACT_DEFINE_INPUT(MatrixPtr<T>, input, getInput, setInput, &InverseTranspose::invalidate)
        REACT_DEFINE_OUTPUT(MatrixPtr<T>, output, getOutput, setOutput, &InverseTranspose::evaluate)

    protected:
        void evaluate() {
#if 0
            auto inversed = Math::Matrix<T>::getInversed(this->input->get());
            if (inversed.defined) {
                auto result = Math::Matrix<T>::getTransposed(inversed.get());
                this->output->set(result);
            }
#else
            auto result = Math::Matrix<T>::getInversed(Math::Matrix<T>::getTransposed(this->input->get()));
            if (result.defined) {
                this->output->set(result.get());
                this->output->commit(false);
            }
#endif
        }

        void invalidate() {
            if (output.get())
                output->invalidate();
        }
    };
}

#endif
