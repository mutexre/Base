#ifndef header_FE390A1B547A
#define header_FE390A1B547A

namespace Math
{
    namespace Distribution
    {
        template <typename T>
        class Unbounded : public Trait<T>
        {
        public:
            virtual Rt::Option<Rt::Range<T>> getRange() override {
                return Rt::Option<Rt::Range<T>>();
            };
        };
    }
}

#endif
