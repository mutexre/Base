#ifndef header_A8AC8CBBCB6D
#define header_A8AC8CBBCB6D

namespace Rt
{
    namespace Memory
    {
        template <typename Size, class IdAlloc>
        class Test : public Rt::Test
        {
        private:
            typedef typename IdAlloc::IdType Id;

            int testManager(Trait<Size, Id>* manager);
            int testMallocManager();
            int testBufferManager();
            int testMultiBuffer();
            int testManagers();

        protected:
            bool debug;

        public:
            Test(bool debug) { this->debug = debug; }
            virtual int test();
        };
    }
}

#include <Runtime/Memory/TestDefinition.h>

#endif
