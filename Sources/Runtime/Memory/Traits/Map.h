#ifndef header_7830FA80026D
#define header_7830FA80026D

namespace Rt {
    namespace Memory {
        namespace Traits
        {
            template <typename Id>
            class Map
            {
            public:
                virtual void* map(Id) = 0;
                virtual void unmap(Id) = 0;
            };
        }
    }
}

#endif
