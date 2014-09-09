#ifndef header_8B84ED75C41C
#define header_8B84ED75C41C

namespace React
{
    template <typename A, typename B>
    class Forward : public Transform<Forward<A, B>>
    {
        REACT_DEFINE_INPUT(ScalarPtr<A>, input, getInput, setInput, &Forward::invalidate)
        REACT_DEFINE_OUTPUT(ScalarPtr<B>, output, getOutput, setOutput, &Forward::evaluate)

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
