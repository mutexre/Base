#ifndef header_13E9334142C5
#define header_13E9334142C5

namespace Rt
{
    namespace Value
    {
        template <typename T>
        class Container : public Trait
        {
        protected:
            T container;

        public:
            virtual ~Container();

            T& getContainer();
            bool isEmpty();
            void clear();
        };
    }
}

#include <Runtime/Value/ContainerDefinition.h>

#endif
