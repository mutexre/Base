#ifndef header_0475afbde84d
#define header_0475afbde84d

namespace React
{
    template <typename T = float, typename I = Rt::u1>
    class SubMatrix : public Transform<T, SubMatrix<T, I>>
    {
    private:
        I size, rowOffset, columnOffset;

    protected:
        virtual void evaluate() {
            if (!this->input[0]->get().empty()) {
                auto& matrix = this->input[0]->get();
                this->output[0]->set(matrix.getSubMatrix(size));
                this->output[0]->commit(true, false);
            }
        }

    public:
        SubMatrix(I size, I rowOffset = 0, I columnOffset = 0) {
            this->size = size;
            this->rowOffset = rowOffset;
            this->columnOffset = columnOffset;
        }
    };
}

#endif
