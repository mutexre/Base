#ifndef header_6D1DF8AE3895
#define header_6D1DF8AE3895

#include <forward_list>
#include <map>

#include <Runtime/Memory/Compound/Base.h>
#include <Runtime/Memory/Compound/Alloc.h>
#include <Runtime/Memory/Compound/Map.h>
#include <Runtime/Memory/Compound/ReadWrite.h>
#include <Runtime/Memory/Compound/Info.h>

namespace Rt {
    namespace Memory {
        namespace Compound {
            template <class T>
            class Trait : public virtual Alloc<T>,
                          public virtual Map<T>,
                          public virtual ReadWrite<T>,
                          public virtual Info<T>
            {};
        }
    }
}

#endif
