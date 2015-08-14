#ifndef header_8B84ED75C41C
#define header_8B84ED75C41C

namespace React
{
    template <typename A, typename B>
    class Forward : public Transform<Forward<A, B>>
    {
        DF_IN(ScalarPtr<A>, input, getInput, setInput, &Forward::invalidate)
        DF_OUT(ScalarPtr<B>, output, getOutput, setOutput, &Forward::evaluate)

    private:
        void invalidate() {
            if (output.get())
                output->invalidate();
        }

        void evaluate() {
            this->commit(output);
        }
    };
}

#endif
