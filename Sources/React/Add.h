#ifndef header_2270d4267aa5
#define header_2270d4267aa5

namespace React
{
    template <typename T = float>
    class Add : public Transform<T, Add<T>>
    {
    protected:
        virtual void evaluate() {
            if (!isThereEmptyInput()) {
                Math::Matrix<T> result(4);

                result.loadIdentity();
                for (auto& x : this->input)
                    result += x->get();

                this->output[0]->set(result);
                this->output[0]->commit(true, false);
            }
        }
    };
}

#endif
