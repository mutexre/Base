#ifndef header_F343A634708D
#define header_F343A634708D

#include <list>
#include <numeric>

namespace Rt
{
    namespace Branching
    {
        template <typename T>
        class Default
        {
        private:
            std::list<T> factors;

        public:
            Default();
            Default(std::list<T> factors);

            std::list<T>& getFactors() const;
            void setFactors(std::list<T> factors);

            std::list<T> computePath(T address);
            T computeAddress(std::list<T> path);
        };
    }
}

#include <Runtime/Branching/DefaultDefinition.h>

#endif
