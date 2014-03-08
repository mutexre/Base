#ifndef header_45A5C670DA1D
#define header_45A5C670DA1D

namespace Rt
{
    namespace IDAllocator
    {
        template <class Id>
        class Counting : public Trait<Id>, public Object
        {
        protected:
            Id current = Id(1);

        public:
            virtual bool get(Id*);
            virtual void put(Id);
        };
    }
}

#include <Runtime/IDAllocator/CountingDefinition.h>

#endif
