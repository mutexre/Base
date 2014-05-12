#ifndef header_EF27FFF18E92
#define header_EF27FFF18E92

namespace React
{
    namespace MathVector
    {
        template <typename T>
        class GetZ : public Transform<GetZ<T>>
        {
            REACT_DEFINE_INPUT(ScalarPtr<Math::Vector<T>>, input, getInput, setInput, &GetZ::invalidate)
            REACT_DEFINE_OUTPUT(ScalarPtr<T>, output, getOutput, setOutput, &GetZ::evaluate)

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
