#ifndef header_EF27FFF18E92
#define header_EF27FFF18E92

namespace React
{
    namespace MathVector
    {
        template <typename T>
        class GetZ : public Transform<GetZ<T>>
        {
            DF_IN(ScalarPtr<Math::Vector<T>>, input, getInput, setInput, &GetZ::invalidate)
            DF_OUT(ScalarPtr<T>, output, getOutput, setOutput, &GetZ::evaluate)

        protected:
            void evaluate() {
                this->output->set(input->get().z);
                this->output->commit(false);
            }

            void invalidate() {
                if (output.get())
                    output->invalidate();
            }
        };
    }
}

#endif
