#ifndef header_767312C15D9C
#define header_767312C15D9C

namespace Rt
{
    namespace IDAllocator
    {
        template <typename Id>
        class Trait
        {
        public:
            typedef Id IdType;
            static const Id none = Id(0);

        protected:
            static const Id maxId = 2 * ((1 << (8 * sizeof(Id) - 1)) - 1) + 1;

        public:
            virtual ~Trait() {};
            virtual bool get(Id*) = 0;
            virtual void put(Id) = 0;
        };
    }
}

#endif
