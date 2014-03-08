#ifndef header_425EC4876BD4
#define header_425EC4876BD4

namespace Rt
{
    namespace Memory
    {
        namespace Multibuffer
        {
            template <typename S = u4, class IdAlloc = IDAllocator::Default<u4>, class B = Buffer<S, IdAlloc>>
            class Default : public virtual Alloc<S, IdAlloc, B>,
                            public virtual Compound::Map<B>,
                            public virtual Compound::ReadWrite<B>
            {
            public:
                typedef IdAlloc IdAllocator;
                typedef typename IdAlloc::IdType Id;
                typedef S Offset;
                typedef S Size;

            public:
                Default();
                Default(Size bufferSize, Value::Map allocators = Value::Map(), Value::Map allocations = Value::Map());
                virtual ~Default() {}
            };

            #include <Runtime/Memory/Multibuffer/DefaultDefinition.h>
        }
    }
}

#endif
