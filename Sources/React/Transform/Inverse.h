#ifndef header_ae91733f9daa
#define header_ae91733f9daa

namespace React
{
    template <typename T = float>
    class Inverse : public Transform<T, Inverse<T>>
    {
    protected:
        virtual void evaluate() {
            if (!this->input[0]->get().empty()) {
                auto result = Math::Matrix<T>::getInversed(this->input[0]->get());
                if (result.defined) {
                    this->output[0]->set(result.get());
                    this->output[0]->commit(true, false);
                    //printf("inv: "); result.get().printMatrix();
                }
            }
        }
    };
}

#endif
