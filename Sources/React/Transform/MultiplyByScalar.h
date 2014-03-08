#ifndef header_aef842abc6e4
#define header_aef842abc6e4

namespace React
{
    template <typename T = float>
    class MultiplyByScalar : public Transform<T, MultiplyByScalar<T>>
    {
    protected:
        T multiplier;

    protected:
        virtual void evaluate() {
            if (!this->input[0]->get().empty()) {
                this->output[0]->set(multiplier * this->input[0]->get());
                this->output[0]->commit(true, false);
            }
        }

    public:
        MultiplyByScalar(T multiplier) {
            this->multiplier = multiplier;
        }
    };
}

#endif
