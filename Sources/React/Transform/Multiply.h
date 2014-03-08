#ifndef header_b840aa535763
#define header_b840aa535763

namespace React
{
    template <typename T = float>
    class Multiply : public Transform<T, Multiply<T>>
    {
    protected:
        virtual void evaluate() {
            if (!this->isThereEmptyInput()) {
                Math::Matrix<T> result(4);

                result.loadIdentity();
                for (auto& x : this->input)
                    result *= x->get();

                this->output[0]->set(result);
                this->output[0]->commit(true, false);
            }
        }
    };
}

#endif
