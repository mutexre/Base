#ifndef header_29FC0BE9239A
#define header_29FC0BE9239A

#include <map>

namespace GL
{
    namespace AUX
    {
        namespace Memory
        {
            template <typename S = Rt::u4, class IdAlloc = Rt::IDAllocator::Default<Rt::u4>, S defaultAlignment = 1>
            class Buffer : public Rt::Memory::Traits::Alloc<typename IdAlloc::IdType>,
                           public Rt::Memory::Traits::Info<typename IdAlloc::IdType>,
                           public GL::Buffer
            {
            public:
                typedef IdAlloc IdAllocator;
                typedef typename IdAlloc::IdType Id;
                typedef S Offset;
                typedef S Size;

            protected:
                Rt::Allocator::Default<Size, IdAlloc> allocator;
                GLenum usage;

                Offset getAllocationOffset(Id);
                virtual Id inheritedAlloc(Rt::Value::Map) override;

            public:
                Buffer(Size, GLenum usage, Rt::Value::Map defaultRequirements = Rt::Value::Map());
                Buffer(Rt::Value::Map properties, Rt::Value::Map defaultRequirements = Rt::Value::Map());
                virtual ~Buffer() {}

                virtual Id alloc(Size, Size alignment = 1);
                virtual void free(Id) override;

                virtual void getAllocationInfo(Id id, Offset*, Size*);
                virtual void getInfo(Size* size, Size* allocatedSize, GLenum* usage);

                virtual Rt::Value::Map getInfo() override;
                virtual Rt::Value::Map getAllocationInfo(Id) override;
            };

            #include <GLCPP/Auxiliary/Memory/BufferDefinition.h>
        }
    }
}

#endif
