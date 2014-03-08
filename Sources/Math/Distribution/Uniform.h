#ifndef header_33499C5C79FE
#define header_33499C5C79FE

#include <random>
#include <chrono>

namespace Math
{
    namespace Distribution
    {
        template <typename T, class RND = std::default_random_engine>
        class Uniform : public Bounded<T>
        {
        private:
            RND generator;
            Rt::Range<T> range;
            Rt::Range<typename RND::result_type> generatorRange;
            bool doRangesHaveEqualLength;
            T offset;

        public:
            Uniform();
            Uniform(Rt::Range<T>);

            virtual T sample() override;
            virtual Rt::Option<Rt::Range<T>> getRange() override;
        };

        #include <Math/Distribution/UniformDefinition.h>
    }
}

#endif
