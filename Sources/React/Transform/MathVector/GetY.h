#ifndef header_7EE1E152DF2A
#define header_7EE1E152DF2A

namespace React
{
    namespace MathVector
    {
        template <typename T>
        class GetY : public Transform<GetY<T>>
        {
            REACT_DEFINE_INPUT(ScalarPtr<Math::Vector<T>>, input, getInput, setInput, &GetY::invalidate)
            REACT_DEFINE_OUTPUT(ScalarPtr<T>, output, getOutput, setOutput, &GetY::evaluate)

        protected:
            void evaluate() {
                this->output->set(input->get().y);
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
