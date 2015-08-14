#ifndef header_015836F6F586
#define header_015836F6F586

namespace React
{
    template <typename T>
    class GetStdVectorDataPtr : public Transform<GetStdVectorDataPtr<T>>
    {
        DF_IN(ScalarPtr<std::vector<T>>, input, getInput, setInput, &GetStdVectorDataPtr::invalidate)
        DF_OUT(ScalarPtr<T*>, output, getOutput, setOutput, &GetStdVectorDataPtr::evaluate)

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
