#ifndef header_332087614AE1
#define header_332087614AE1

namespace Rt
{
    namespace Memory
    {
        namespace Compound
        {
            template <class A>
            class ReadWrite : public virtual Base<A>,
                              public Traits::ReadWrite<typename A::Size, typename A::Offset, typename A::Id>
            {
            public:
                typedef typename A::IdAllocator IdAllocator;
                typedef typename A::Id Id;
                typedef typename A::Offset Offset;
                typedef typename A::Size Size;

            public:
                virtual void read(Id ID, Offset offset, Size size, void* ptr) override;
                virtual void write(Id ID, Offset offset, Size size, const void* ptr) override;
            };

            #include <Runtime/Memory/Compound/ReadWriteDefinition.h>
        }
    }
}

#endif
