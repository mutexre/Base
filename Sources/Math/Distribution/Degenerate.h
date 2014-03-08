#ifndef header_C121BAEA22F4
#define header_C121BAEA22F4

namespace Math
{
    namespace Distribution
    {
        template <typename T>
        class Degenerate : public Bounded<T>
        {
        private:
            T value;
            Rt::Range<T> range;

        public:
            Degenerate(T value) {
                this->value = value;
                range = Rt::Range<T>(value);
            }

            virtual T sample() override {
                return value;
            }

            virtual Rt::Option<Rt::Range<T>> getRange() override {
                return Rt::Option<Rt::Range<T>>(range);
            }
        };

        #include <Math/Distribution/Degenerate.h>
    }
}

#endif
