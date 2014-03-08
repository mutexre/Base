#ifndef header_A09C95041EA6
#define header_A09C95041EA6

namespace Rt
{
    namespace Memory
    {
        namespace Compound
        {
            template <class A>
            class Base
            {
            public:
                typedef typename A::Id Id;

            protected:
                /* Map of allocation's IDs to pairs consisting of an allocator and the allocation ID inside that allocator */
                std::map<Id, std::pair<A*, Id>> ids2allocations;
            };
        }
    }
}

#endif
