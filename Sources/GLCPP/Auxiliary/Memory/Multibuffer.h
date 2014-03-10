#ifndef header_B7A6D4720E1F
#define header_B7A6D4720E1F

namespace GL
{
    namespace AUX
    {
        namespace Memory
        {
            template <typename S = Rt::u4, class IdAlloc = Rt::IDAllocator::Default<Rt::u4>, class A = Buffer<S, IdAlloc>, S defaultAlignment = 1>
            class Multibuffer : public virtual Rt::Memory::Multibuffer::Alloc<S, IdAlloc, A, defaultAlignment>,
                                public virtual Rt::Memory::Compound::Info<A>
            {
            public:
                typedef IdAlloc IdAllocator;
                typedef typename IdAlloc::IdType Id;
                typedef S Offset;
                typedef S Size;

            private:
                virtual Rt::Value::Map inheritedGenerateAllocatorProperties(Rt::Value::Map requirements) override;
                virtual bool doAllocatorSatisfyRequirements(A* allocator, Rt::Value::Map) override;

            public:
                Multibuffer(Size bufferSize,
                            Rt::Value::Map defaultAllocatorsProperties = Rt::Value::Map(),
                            Rt::Value::Map defaultAllocationsRequirements = Rt::Value::Map());

                virtual ~Multibuffer() {}

                virtual Id alloc(Size, GLenum usage, Size alignment);
                //virtual Rt::Value::Map getAllocationInfo(Id) override;
            };

            #include <GLCPP/Auxiliary/Memory/MultibufferDefinition.h>
        }
    }
}

#endif
