#ifndef header_787ECF2AA685
#define header_787ECF2AA685

#include <Runtime/Memory/Traits/Alloc.h>
#include <Runtime/Memory/Traits/Map.h>
#include <Runtime/Memory/Traits/ReadWrite.h>
#include <Runtime/Memory/Traits/Info.h>

namespace Rt
{
    namespace Memory
    {
        template <typename Size, typename Id>
        class Trait : public Traits::Alloc<Id>,
                      public Traits::Map<Id>,
                      public Traits::ReadWrite<Size, Size, Id>,
                      public Traits::Info<Id>
        {};
    }
}

#endif
