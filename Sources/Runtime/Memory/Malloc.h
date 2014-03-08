#ifndef header_E307731F9306
#define header_E307731F9306

#include <map>

namespace Rt
{
    namespace Memory
    {
        template <typename Size, class IdAlloc, Size defaultAlignment = 1>
        class Malloc : public Trait<Size, typename IdAlloc::IdType>,
                       public Object
        {
        public:
            typedef typename IdAlloc::IdType Id;

        protected:
            struct Allocation {
                u1* ptr;
                u1* dataPtr;

                Allocation() : ptr(nullptr), dataPtr(nullptr) {}
                Allocation(u1* ptr, u1* dataPtr) {
                    this->ptr = ptr;
                    this->dataPtr = dataPtr;
                }
            };

        protected:
            IdAlloc idAllocator;
            std::map<Id, Allocation> allocations;

        protected:
            void* getAllocationPtr(Id);
            virtual Id inheritedAlloc(Value::Map) override;

        public:
            Malloc();
            Malloc(Value::Map defaultRequirements);
            virtual ~Malloc();

            virtual Id alloc(Size);
            virtual Id alloc(Size, Size alignment);
            virtual void free(Id) override;

            virtual void* map(Id) override;
            virtual void unmap(Id) override;

            virtual void read(Id, Size offset, Size size, void*) override;
            virtual void write(Id, Size offset, Size size, const void*) override;

            virtual Value::Map getInfo() override;
        };

        #include <Runtime/Memory/MallocDefinition.h>
    }
}

#endif
