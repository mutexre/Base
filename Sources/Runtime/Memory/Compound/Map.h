#ifndef header_EA0FEBDF01BD
#define header_EA0FEBDF01BD

namespace Rt
{
    namespace Memory
    {
        namespace Compound
        {
            template <class T>
            class Map : public virtual Base<T>,
                        public Traits::Map<typename T::Id>
            {
            public:
                typedef typename T::IdAllocator IdAllocator;
                typedef typename T::Id Id;

            public:
                virtual ~Map() {}

                virtual void* map(Id ID) override;
                virtual void unmap(Id ID) override;
            };

            #include <Runtime/Memory/Compound/MapDefinition.h>
        }
    }
}

#endif
