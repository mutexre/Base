#ifndef header_33689F1F9822
#define header_33689F1F9822

namespace Rt
{
    namespace Value
    {
        class Provider {
        public:
            virtual void evaluate() = 0;
        };

        class Lazy
        {
        public:
            class CannotEvaluate : std::exception {};

        private:
            bool valid;
            std::weak_ptr<Provider> provider;

        protected:
            Lazy() : valid(false) {}
            Lazy(std::shared_ptr<Provider> provider) {
                setProvider(provider);
            }

            void evaluateIfNeeded() {
                if (!valid) {
                    auto prov = provider.lock();
                    if (prov) {
                        prov->evaluate();
                        setValidity(true);
                    }
                    else
                        throw CannotEvaluate();
                }
            }

        public:
            void setProvider(std::shared_ptr<Provider> provider) {
                this->provider = provider;
            }

            void setValidity(bool value) {
                valid = value;
            }

            void invalidate() {
                setValidity(false);
            }

            bool isValid() const {
                return valid;
            }
        };

        class Trait : public Object,
                      public Versioned<Rt::u8>,
                      public Observable<>,
                      public Lazy
        {
        public:
            enum class Type {
                None, Scalar, Uuid, Map, Vector
            };

        protected:
            Type type;

        protected:
			Trait() : type(Type::None) {}
            Trait(Type type);

        public:
            virtual ~Trait() {};

            virtual Type getType() const;
            virtual void traverseTree(std::function<void (std::shared_ptr<Trait>)> f);

            virtual void commit(bool valid = true, bool notify = true);
        };
    }
}

#endif
