#ifndef header_8f8fffc293b9
#define header_8f8fffc293b9

namespace React
{
    template <typename T = float>
    class Negate : public Transform<T, Negate<T>>
    {
    protected:
        virtual void evaluate() {
            if (!this->input[0]->get().empty()) {
                this->output[0]->set(this->input[0]->get().multiplyByScalar(T(-1)));
                this->output[0]->commit(true, false);
            }
        }
    };
}

#endif
