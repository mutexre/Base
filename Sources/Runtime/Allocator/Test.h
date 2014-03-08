#ifndef header_CAF8C061520B
#define header_CAF8C061520B

namespace Rt
{
    namespace Allocator
    {
        template <typename Size, class IdAlloc>
        class Test : public Rt::Test
        {
        private:
            typedef typename IdAlloc::IdType Id;

            void printAllocator(Allocator::Default<Size, IdAlloc>&);
            int deleteNonExistingId(Allocator::Default<Size, IdAlloc>&, Id);
            int testAllocator(Size, u2 n, bool debug);
            int testRandomAllocations(Size min, Size max, u2 n);

        public:
            virtual int test();
        };
    }
}

#include <Runtime/Allocator/TestDefinition.h>

#endif
