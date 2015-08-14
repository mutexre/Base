#ifndef header_b840aa535763
#define header_b840aa535763

namespace React
{
    template <typename T>
    class Multiply : public Transform<Multiply<T>>
    {
        REACT_DEFINE_VECTOR_INPUT(ScalarPtr<T>, input, getInput, setInput, addInput, &Multiply::invalidate)
        DF_OUT(ScalarPtr<T>, output, getOutput, setOutput, &Multiply::evaluate)

    protected:
        void evaluate() {
            T result = input[0]->get();

            if (input.size() > 1)
                for (auto i = 1; i < input.size(); i++)
                    result *= input[i]->get();

            output->set(result);
            output->commit(false);
        }

        void invalidate() {
            if (output.get())
                output->invalidate();
        }
    };
}

#endif
