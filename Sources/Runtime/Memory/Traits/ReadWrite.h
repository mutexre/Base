#ifndef header_57D4ECF969BD
#define header_57D4ECF969BD

namespace Rt {
    namespace Memory {
        namespace Traits
        {
            template <typename Size, typename Offset, typename Id>
            class ReadWrite
            {
            public:
                virtual void read(Id, Offset offset, Size size, void*) = 0;
                virtual void write(Id, Offset offset, Size size, const void*) = 0;
            };
        }
    }
}

#endif
