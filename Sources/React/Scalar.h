#ifndef header_E74D401CE62D
#define header_E74D401CE62D

namespace React
{
    template <typename T>
    class Scalar : public Rt::Object,
                   public Rt::Versioned<Rt::u8>,
                   public Observable<2>
    {
    protected:
        T val;
        bool valid;
        std::weak_ptr<Provider> provider;

    public:
        class CannotEvaluate : std::exception {};

    protected:
        void evaluateIfNeeded() {
            if (!valid) {
                auto prov = provider.lock();
                if (prov)
                    prov->evaluate(this);
                else
                    throw CannotEvaluate();
            }
        }

    public:
        Scalar() {
            setValidity(true);
        }

        Scalar(T value) : Scalar() {
            this->val = value;
        }

        virtual ~Scalar() {};

        virtual T& value() {
            evaluateIfNeeded();
            return val;
        }

        virtual T& currentValue() {
            return val;
        }

        virtual void set(T value) {
            this->val = value;
        }

        void setProvider(std::shared_ptr<Provider> provider) {
            this->provider = provider;
            setValidity(false);
        }

        void setValidity(bool value) {
            valid = value;
        }

        bool isValid() const {
            return valid;
        }

        virtual void commit(bool notify = true) {
            incrementVersion();
            setValidity(true);
            if (notify) this->notify(this);
        }

        virtual void invalidate() {
            setValidity(false);
            this->notify(this);
        }
    };

    template <typename T = float>
    using ScalarPtr = std::shared_ptr<Scalar<T>>;

    template <typename T = float>
    using ScalarUniquePtr = std::unique_ptr<Scalar<T>>;

    template <typename T = float>
    using ScalarWeakPtr = std::weak_ptr<Scalar<T>>;

    template <typename T = float>
    ScalarPtr<T> makeScalarPtr() {
        return std::make_shared<Scalar<T>>();
    }

    template <typename T = float>
    ScalarPtr<T> makeScalarPtr(T value) {
        return std::make_shared<Scalar<T>>(value);
    }

    template <typename T, typename ...Args>
    ScalarPtr<T> makeScalarPtr(Args&& ...args) {
        return std::make_shared<Scalar<T>>(T(args...));
    }
}

#endif
