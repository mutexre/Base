#ifndef header_8AE1639498A9
#define header_8AE1639498A9

namespace Rt
{
    namespace Value
    {
        template <typename T>
        class Scalar : public Trait
        {
        protected:
            T value;

        public:
            Scalar();
            Scalar(T value);

            T& get();
            void set(T value);
        };
    }
}

#include <Runtime/Value/ScalarDefinition.h>

#endif
