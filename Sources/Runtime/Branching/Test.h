#ifndef header_DE20F85E3C98
#define header_DE20F85E3C98

namespace Rt
{
    namespace Branching
    {
        template <typename T>
        class Test : public Rt::Test
        {
        private:
            int testComputePath(T i, std::list<T> branchingFactors, std::list<T> expectedResult);

        public:
            virtual int test();
        };
    }
}

#include <Runtime/Branching/TestDefinition.h>

#endif
