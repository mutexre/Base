#ifndef header_D3BC4E53EAE1
#define header_D3BC4E53EAE1

namespace Rt
{
    namespace Type
    {
        template <typename T, typename I>
        class Test : public Rt::Test
        {
        private:

        public:
            virtual int test();
        };
    }
}

#include <Runtime/Type/TestDefinition.h>

#endif
