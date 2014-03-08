#ifndef header_AC3DC5B43040
#define header_AC3DC5B43040

namespace React
{
    template <typename T, class This>
    class Transform : public Rt::Object,
                      public Rt::Value::Provider,
                      public std::enable_shared_from_this<This>
    {
    protected:
        std::vector<ValuePtr<T>> input;
        std::vector<ValuePtr<T>> output;
        std::map<ValuePtr<T>, boost::signals2::connection> connections;

    protected:
        void invalidateSuccessors() {
            for (auto& out : output) {   
                out->invalidate();
                out->notify(this);
            }
        }

        void inputDidChange(void*) {
            invalidateSuccessors();
        }

        virtual void evaluate() = 0;

        bool isThereEmptyInput() {
            return std::find_if(this->input.begin(), this->input.end(), [](ValuePtr<T> x) -> bool {
                return x->get().empty();
            }) != input.end();
        }

        template <typename I>
        boost::signals2::connection observeInput(const ValuePtr<I>& in) {
            return in->addObserver(Rt::Observable<>::Signal::slot_type(&Transform::inputDidChange, this, _1).track_foreign(this->shared_from_this()));
        }

    public:
        Transform() {}

        Transform(const std::string& name) {
            setName(name);
        }

        const ValuePtr<T>& getInput(Rt::u2 index) const {
            return input[index];
        }

        const ValuePtr<T>& getInput() const {
            return getInput(0);
        }

        void addInput(ValuePtr<T> in) {
            input.push_back(in);
            connections[in] = observeInput(in);
            invalidateSuccessors();
        }

        void setInput(Rt::u2 index, ValuePtr<T> in) {
            input[index] = in;
            connections[in] = observeInput(in);
            invalidateSuccessors();
        }

        void setInput(ValuePtr<T> in) {
            setInput(0, in);
        }

        ValuePtr<T> getOutput(Rt::u2 index) const {
            return output[index];
        }

        ValuePtr<T> getOutput() {
            return getOutput(0);
        }

        void addOutput(ValuePtr<T> out) {
            output.push_back(out);
            out->setProvider(this->shared_from_this());
            invalidateSuccessors();
        }

        void setOutput(Rt::u2 index, ValuePtr<T> out) {
            output[index] = out;
            out->setProvider(this->shared_from_this());
            invalidateSuccessors();
        }

        void setOutput(ValuePtr<T> out) {
            setOutput(0, out);
        }
    };
 }

#endif
