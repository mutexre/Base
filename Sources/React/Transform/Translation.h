#ifndef header_9c0bc1fe53e3
#define header_9c0bc1fe53e3

namespace React
{
    template <typename T>
    class Translation : public Transform<Translation<T>>
    {
        DF_IN(ScalarPtr<T>, x, getX, setX, &Translation::invalidate)
        DF_IN(ScalarPtr<T>, y, getY, setY, &Translation::invalidate)
        DF_IN(ScalarPtr<T>, z, getZ, setZ, &Translation::invalidate)
        DF_OUT(MatrixPtr<T>, output, getOutput, setOutput, &Translation::evaluate)

    protected:
        void evaluate() {
            this->output->set(Math::Translation<T>(this->x->get(), this->y->get(), this->z->get()));
            this->output->commit(false);
        }

        void invalidate() {
            if (output.get())
                output->invalidate();
        }
    };
}

#endif
