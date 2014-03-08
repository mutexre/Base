#ifndef header_9307debb5fe5
#define header_9307debb5fe5

namespace React
{
    template <typename T = float>
    class InverseTranspose : public Transform<T, InverseTranspose<T>>
    {
    protected:
        virtual void evaluate() {
            if (!this->input[0]->get().empty()) {
#if 0
                auto inversed = Math::Matrix<T>::getInversed(this->input[0]->get());
                if (inversed.defined) {
                    auto result = Math::Matrix<T>::getTransposed(inversed.get());
                    this->output[0]->set(result);
                    //printf("inv transpose: "); result.printMatrix();
                }
#else
                auto result = Math::Matrix<T>::getInversed(Math::Matrix<T>::getTransposed(this->input[0]->get()));
                if (result.defined) {
                    this->output[0]->set(result.get());
                    this->output[0]->commit(true, false);
                    //printf("inv transpose: "); result.printMatrix();
                }
#endif
            }
        }
    };
}

#endif
