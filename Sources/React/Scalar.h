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
        T value;
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
        Scalar() {}

        Scalar(T value) {
            this->value = value;
        }

        virtual ~Scalar() {};

        virtual T& get() {
            evaluateIfNeeded();
            return value;
        }

        virtual void set(T value) {
            this->value = value;
        }

        void setProvider(std::shared_ptr<Provider> provider) {
            this->provider = provider;
        }

        void setValidity(bool value) {
            valid = value;
            //this->notify(valid ? 0 : 1, this);
        }

        bool isValid() const {
            return valid;
        }

        virtual void commit(bool notify = true) {
            incrementVersion();
            setValidity(true);
            if (notify) this->notify(this);
        }
    };

    template <typename T = float>
    using ScalarPtr = std::shared_ptr<Scalar<T>>;

    template <typename T = float>
    using ScalarUniquePtr = std::unique_ptr<Scalar<T>>;

    template <typename T = float>
    using ScalarWeakPtr = std::weak_ptr<Scalar<T>>;

    template <typename T = float>
    ScalarPtr<T> makeScalar() {
        return std::make_shared<Scalar<T>>();
    }

    template <typename T = float>
    ScalarPtr<T> makeScalar(T value) {
        return std::make_shared<Scalar<T>>(value);
    }
}

#endif
