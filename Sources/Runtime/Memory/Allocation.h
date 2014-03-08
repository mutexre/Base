#ifndef header_946EC6EAB120
#define header_946EC6EAB120

namespace Rt
{
    namespace Memory
    {
        template <typename A>
        class Allocation
        {
        protected:
            std::shared_ptr<A> allocator;
            typename A::Id id;

			Allocation() : id(IDAllocator::Trait<typename A::Id>::none) {}

        public:
            Allocation(std::shared_ptr<A>, typename A::Id);
            Allocation(std::shared_ptr<A>);
            virtual ~Allocation();

            std::shared_ptr<A> getAllocator() const;
            typename A::Id getId() const;

            virtual void instantiate(Value::Map);
            virtual Value::Map getInfo();
        };

        #include <Runtime/Memory/AllocationDefinition.h>
    }
}

#endif
