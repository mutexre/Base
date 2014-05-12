#ifndef header_AC3DC5B43040
#define header_AC3DC5B43040

namespace React
{
    template <class This>
    class Transform : public Rt::Object,
                      public Provider,
                      public std::enable_shared_from_this<This>
    {
    protected:
        std::map<void*, void (This::*)()> invalidators;
        std::map<void*, void (This::*)()> evaluators;

    protected:
        void invoke(void (This::*fn)()) {
            (static_cast<This*>(this)->*fn)();
        }

        void inputDidChange(void* input) {
            invoke(invalidators[input]);
        }

        void evaluate(void* output) {
            invoke(evaluators[output]);
        }

        template <typename T>
        Observable<2>::Connection observe(Scalar<T>* var) {
            return var->addObserver(Observable<2>::Observer(&Transform::inputDidChange, this, _1).track_foreign(this->shared_from_this()));
        }

        template <typename T>
        void commit(T& output) {
            output->commit(false);
        }

    public:
        Transform() {}

        Transform(const std::string& name) {
            setName(name);
        }
    };
 }

#endif
