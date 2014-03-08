#ifndef header_2b01d8d4aafd
#define header_2b01d8d4aafd

namespace React
{
    namespace Logic
    {
        template <typename T = bool>
        class And : public Transform<T, And<T>>
        {
        protected:
            virtual void evaluate() {
                if (!this->input[0]->get().empty() && !this->input[1]->get().empty()) {
                    this->output[0]->set(this->input[0]->get(0) && this->input[1]->get(0));
                    this->output[0]->commit(true, false);
                }
            }
        };
    }
}

#endif
