#ifndef header_9c0bc1fe53e3
#define header_9c0bc1fe53e3

namespace React
{
    template <typename T = float>
    class Translation : public Transform<T, Translation<T>>
    {
    protected:
        virtual void evaluate() {
            if (this->input.size() == 3 && !this->isThereEmptyInput()) {
                this->output[0]->set(Math::Translation<T>(this->input[0]->get().get(), this->input[1]->get().get(), this->input[2]->get().get()));
                this->output[0]->commit(true, false);
            }
        }
    };
}

#endif
