#ifndef header_AB84599E61FD
#define header_AB84599E61FD

namespace SG
{
    class Piece
    {
    protected:
        React::ScalarPtr<std::shared_ptr<DataBinding>> dataBinding;
        React::ScalarPtr<std::shared_ptr<DrawCall>> drawCall;

    public:
        Piece() {}

        Piece(React::ScalarPtr<std::shared_ptr<DataBinding>> dataBinding, React::ScalarPtr<std::shared_ptr<DrawCall>> drawCall) {
            this->dataBinding = dataBinding;
            this->drawCall = drawCall;
        }

        virtual ~Piece() {}

        React::ScalarPtr<std::shared_ptr<DataBinding>> getDataBinding() const {
            return dataBinding;
        }

        void setDataBinding(React::ScalarPtr<std::shared_ptr<DataBinding>> dataBinding) {
            this->dataBinding = dataBinding;
        }

        React::ScalarPtr<std::shared_ptr<DrawCall>> getDrawCall() const {
            return drawCall;
        }

        void setDrawCall(React::ScalarPtr<std::shared_ptr<DrawCall>> drawCall) {
            this->drawCall = drawCall;
        }

        void render() {
            auto& dataBindingValue = dataBinding->value();
            dataBindingValue->prepare();
            (*drawCall->value())();
            dataBindingValue->complete();
        }
    };
}

#endif
