#ifndef header_007F4F1BA7CE
#define header_007F4F1BA7CE

namespace React
{
    namespace MathVector
    {
        template <typename T>
        class GetX : public Transform<GetX<T>>
        {
            REACT_DEFINE_INPUT(ScalarPtr<Math::Vector<T>>, input, getInput, setInput, &GetX::invalidate)
            REACT_DEFINE_OUTPUT(ScalarPtr<T>, output, getOutput, setOutput, &GetX::evaluate)

        protected:
            void evaluate() {
                this->output->set(input->get().x);
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
