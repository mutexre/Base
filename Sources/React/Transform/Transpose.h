#ifndef header_4d089dc84ef2
#define header_4d089dc84ef2

namespace React
{
    template <typename T = float>
    class Transpose : public Transform<T, Transpose<T>>
    {
    protected:
        virtual void evaluate() {
            if (!this->input[0]->get().empty()) {
                auto result = Math::Matrix<T>::getTransposed(this->input[0]->get());
                this->output[0]->set(result);
                this->output[0]->commit(true, false);
                //printf("transpose: "); result.printMatrix();
            }
        }
    };
}

#endif
