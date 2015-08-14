#ifndef header_AD70585E5EC6
#define header_AD70585E5EC6

namespace React
{
    template <typename T1, typename T2>
    class MakePair : Transform<MakePair<T1, T2>>
    {
        using OutputType = std::pair<T1, T2>;

        DF_IN(ScalarPtr<T1>, first, getFirst, setFirst, &MakePair::invalidate)
        DF_IN(ScalarPtr<T1>, second, getSecond, setSecond, &MakePair::invalidate)
        DF_OUT(ScalarPtr<OutputType>, output, getOutput, setOutput, &MakePair::evaluate)

    private:
        void invalidate() {
            if (output.get())
                output->invalidate();
        }

        void evaluate() {
            auto& output = this->output->currentValue();
            output.first = first->value();
            output.second = second->value();
            this->commit(this->output);
        }
    };
}

#endif
