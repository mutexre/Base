#ifndef header_9B59852A6E14
#define header_9B59852A6E14

namespace Math
{
    namespace Distribution
    {
        template <typename T>
        class Trait : public Rt::Object
        {
        public:
            virtual T sample() = 0;
            virtual Rt::Option<Rt::Range<T>> getRange() = 0;
        };
    }
}

#endif
