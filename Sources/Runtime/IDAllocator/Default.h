#ifndef header_45A5C670DA1D
#define header_45A5C670DA1D

namespace Rt
{
    namespace IDAllocator
    {
        template <typename Id>
        class Default : public Trait<Id>, public Object
        {
        protected:
            Id current;

        public:
			Default() : current(Trait<Id>::none + Id(1)) {}
            virtual bool get(Id*);
            virtual void put(Id);
        };
    }
}

#include <Runtime/IDAllocator/DefaultDefinition.h>

#endif
