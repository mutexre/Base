#ifndef header_CC909BF6F07C
#define header_CC909BF6F07C

namespace Math
{
    namespace Distribution
    {
        template <typename T>
        class Bounded : public Trait<T>
        {
        public:
            virtual Rt::Range<T> getBoundedRange() {
                return this->getRange().get();
            }
        };
    }
}

#endif
