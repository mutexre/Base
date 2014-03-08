#ifndef header_30BD3BBF9D55
#define header_30BD3BBF9D55

namespace Rt
{
    namespace Memory
    {
        namespace Multibuffer
        {
            template <typename S = u4, class IdAlloc = IDAllocator::Default<u4>, class A = Buffer<S, IdAlloc>, S defaultAlignment = 1>
            class Alloc : public Compound::Alloc<A>
            {
            public:
                typedef IdAlloc IdAllocator;
                typedef typename IdAlloc::IdType Id;
                typedef S Offset;
                typedef S Size;

            protected:
                Size bufferSize;

            protected:
                virtual Value::Map inheritedGenerateAllocatorProperties(Value::Map requirements) override;
                virtual bool doAllocatorSatisfyRequirements(A* allocator, Value::Map) override;

            public:
                Alloc(Size bufferSize,
                      Value::Map defaultAllocatorsProperties = Value::Map(),
                      Value::Map defaultAllocationsRequirements = Value::Map());

                virtual ~Alloc() {}
            };

            #include <Runtime/Memory/Multibuffer/AllocDefinition.h>
        }
    }
}

#endif
