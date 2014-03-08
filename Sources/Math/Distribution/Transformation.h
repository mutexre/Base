#ifndef header_7C6E8D2DFAD5
#define header_7C6E8D2DFAD5

#include <functional>

namespace Math
{
    namespace Distribution
    {
        template <typename T1, typename T2>
        class Transformation : public Trait<T2>
        {
        protected:
            Trait<T1>* distr;
            std::function<T2(T1)> f;
            bool monotonic;

        public:
            Transformation() : monotonic(false) {}
            Transformation(Trait<T1>* distr, std::function<T2(T1)> f);

            virtual bool isMonotonic() const;
            virtual void setMonotonicity(bool value);

            virtual T2 sample() override;
            virtual Rt::Option<Rt::Range<T2>> getRange() override;
        };

        #include <Math/Distribution/TransformationDefinition.h>
    }
}

#endif