#ifndef header_2270d4267aa5
#define header_2270d4267aa5

namespace React
{
    template <typename T>
    class Add : public Transform<Add<T>>
    {
        REACT_DEFINE_VECTOR_INPUT(ScalarPtr<T>, input, getInput, setInput, addInput, &Add::invalidate)
        DF_OUT(ScalarPtr<T>, output, getOutput, setOutput, &Add::evaluate)

    protected:
        void evaluate() {
            T result = input[0]->get();

            if (input.size() > 1)
                for (auto i = 1; i < input.size(); i++)
                    result += input[i]->get();

            this->output->set(result);
            this->output->commit(false);
        }

        void invalidate() {
            if (output.get())
                output->invalidate();
        }
    };
}

#endif
