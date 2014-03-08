#ifndef header_B74065E46C93
#define header_B74065E46C93

namespace Rt
{
    namespace Memory
    {
        namespace Compound
        {
            template <class A>
            class Alloc : public virtual Base<A>,
                          public Traits::Alloc<typename A::Id>
            {
            public:
                typedef typename A::IdAllocator IdAllocator;
                typedef typename A::Id Id;

            protected:
                IdAllocator idAlloc;
                std::forward_list<A*> allocators;
                std::map<A*, u8> allocators2useCounts;
                Value::Map defaultAllocatorsProperties;

            private:
                Value::Map generateAllocatorProperties(Value::Map requirements);
                Id tryAlloc(A* allocator, Value::Map& requirements);

            protected:
                virtual Value::Map inheritedGenerateAllocatorProperties(Value::Map requirements);
                virtual A* createAllocator(Value::Map properties);
                virtual bool doAllocatorSatisfyRequirements(A*, Value::Map) = 0;

                virtual Id inheritedAlloc(Value::Map) override;

            public:
                Alloc(Value::Map defaultAllocatorsProperties = Value::Map(), Value::Map defaultAllocationsRequirements = Value::Map());
                virtual ~Alloc();

                virtual Value::Map getDefaultAllocatorsProperties();
                virtual void setDefaultAllocatorsProperties(Value::Map);

                virtual void free(Id) override;
            };

            #include <Runtime/Memory/Compound/AllocDefinition.h>
        }
    }
}

#endif
