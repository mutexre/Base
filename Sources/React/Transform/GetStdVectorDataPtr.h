#ifndef header_015836F6F586
#define header_015836F6F586

namespace React
{
    template <typename T>
    class GetStdVectorDataPtr : public Transform<GetStdVectorDataPtr<T>>
    {
        REACT_DEFINE_INPUT(ScalarPtr<std::vector<T>>, input, getInput, setInput, &GetStdVectorDataPtr::invalidate)
        REACT_DEFINE_OUTPUT(ScalarPtr<T*>, output, getOutput, setOutput, &GetStdVectorDataPtr::evaluate)

    private:
        void invalidate() {
            if (output.get())
                output->invalidate();
        }

        void evaluate() {
            output->set(input->value());
            this->commit(this->output);
        }
    };
}

#endif
