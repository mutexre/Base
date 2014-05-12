#ifndef header_4d089dc84ef2
#define header_4d089dc84ef2

namespace React
{
    template <typename T>
    class Transpose : public Transform<Transpose<T>>
    {
        REACT_DEFINE_INPUT(MatrixPtr<T>, input, getInput, setInput, &Transpose::invalidate)
        REACT_DEFINE_OUTPUT(MatrixPtr<T>, output, getOutput, setOutput, &Transpose::evaluate)

    protected:
        void evaluate() {
            auto result = Math::Matrix<T>::getTransposed(this->input->get());
            this->output->set(result);
            this->output->commit(false);
            //printf("transpose: "); result.printMatrix();
        }

        void invalidate() {
            if (output.get())
                output->invalidate();
        }
    };
}

#endif
