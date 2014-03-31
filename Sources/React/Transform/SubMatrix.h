#ifndef header_0475afbde84d
#define header_0475afbde84d

namespace React
{
    template <typename T, typename I = Rt::u1>
    class SubMatrix : public Transform<SubMatrix<T, I>>
    {
        REACT_DEFINE_INPUT(MatrixPtr<T>, input, getInput, setInput, &SubMatrix::invalidate)
        REACT_DEFINE_OUTPUT(MatrixPtr<T>, output, getOutput, setOutput, &SubMatrix::evaluate)

    protected:
        I size, rowOffset, columnOffset;

    protected:
        void evaluate() {
            auto& matrix = input->get();
            this->output->set(matrix.getSubMatrix(size));
            this->output->commit(false);
        }

        void invalidate() {
            if (output.get()) {
                output->invalidate();
                output->notify(this);
            }
        }

    public:
        SubMatrix(I size, I rowOffset = 0, I columnOffset = 0) {
            this->size = size;
            this->rowOffset = rowOffset;
            this->columnOffset = columnOffset;
            output->set(Math::makeMatrix(size));
        }
    };
}

#endif
