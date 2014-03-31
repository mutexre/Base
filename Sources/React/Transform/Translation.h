#ifndef header_9c0bc1fe53e3
#define header_9c0bc1fe53e3

namespace React
{
    template <typename T>
    class Translation : public Transform<Translation<T>>
    {
        REACT_DEFINE_INPUT(ScalarPtr<T>, x, getX, setX, &Translation::invalidate)
        REACT_DEFINE_INPUT(ScalarPtr<T>, y, getY, setY, &Translation::invalidate)
        REACT_DEFINE_INPUT(ScalarPtr<T>, z, getZ, setZ, &Translation::invalidate)
        REACT_DEFINE_OUTPUT(MatrixPtr<T>, output, getOutput, setOutput, &Translation::evaluate)

    protected:
        void evaluate() {
            this->output->set(Math::Translation<T>(this->x->get(), this->y->get(), this->z->get()));
            this->output->commit(false);
        }

        void invalidate() {
            if (output.get()) {
                output->invalidate();
                output->notify(this);
            }
        }
    };
}

#endif
