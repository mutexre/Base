#ifndef header_17A539579413
#define header_17A539579413

#include <map>

namespace Rt
{
    namespace Memory
    {
        template <typename S, class IdAlloc, S defaultAlignment = 1>
        class Buffer : public Trait<S, typename IdAlloc::IdType>,
                       public Object
        {
        public:
            typedef IdAlloc IdAllocator;
            typedef typename IdAlloc::IdType Id;
            typedef S Offset;
            typedef S Size;

        protected:
            u1* buffer;
            Allocator::Default<Size, IdAlloc> allocator;

            void* getAllocationPtr(Id);
            virtual Id inheritedAlloc(Value::Map) override;

        public:
			Buffer() : buffer(nullptr) {}
            Buffer(Size, Value::Map defaultRequirements = Value::Map());
            Buffer(Value::Map properties, Value::Map defaultRequirements = Value::Map());
            virtual ~Buffer();

            virtual Id alloc(Size size);
            virtual Id alloc(Size size, Size alignment);
            virtual void free(Id) override;

            virtual void* map(Id) override;
            virtual void unmap(Id) override;

            virtual void read(Id, Offset, Size, void*) override;
            virtual void write(Id, Offset, Size, const void*) override;

            virtual void getInfo(Size* size, Size* allocatedSize);
            virtual void getAllocationInfo(Id, Offset*, Size*);

            virtual Value::Map getInfo() override;
            virtual Value::Map getAllocationInfo(Id) override;
        };

        #include <Runtime/Memory/BufferDefinition.h>
    }
}

#endif
