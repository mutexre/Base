#ifndef header_C604CC4633E1
#define header_C604CC4633E1

namespace Rt
{
    namespace Memory
    {
        namespace Compound
        {
            template <class A>
            class Info : public virtual Base<A>,
                         public Traits::Info<typename A::Id>
            {
            public:
                typedef typename A::IdAllocator IdAllocator;
                typedef typename A::Id Id;

            public:
                virtual Value::Map getAllocationInfo(Id) override;
            };

            #include <Runtime/Memory/Compound/InfoDefinition.h>
        }
    }
}

#endif
