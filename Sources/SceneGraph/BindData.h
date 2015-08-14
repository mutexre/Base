#ifndef header_FA2CF105889B
#define header_FA2CF105889B

namespace SG
{
    class BindData : public React::Transform<BindData>
    {
        DF_IN(React::ScalarPtr<std::shared_ptr<Data>>, data, getData, setData, &BindData::invalidate)
        DF_IN(React::ScalarPtr<std::shared_ptr<Program>>, program, getPragram, setProgram, &BindData::invalidate)
        DF_IN(React::ScalarPtr<std::set<std::string>>, disabledArrays, getDisabledArrays, setDisabledArrays, &BindData::invalidate)
        DF_OUT(React::ScalarPtr<std::shared_ptr<DataBinding>>, dataBinding, getDataBinding, setDataBinding, &BindData::evaluate)

    protected:
        void evaluate() {
            dataBinding->currentValue()->bind(data->value(), program->value(), disabledArrays->value());
            commit(dataBinding);
        }

        void invalidate() {
            if (dataBinding.get())
                dataBinding->invalidate();
        }
    };
}

#endif
