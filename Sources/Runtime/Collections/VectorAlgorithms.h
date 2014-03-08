#ifndef header_2419147669DF
#define header_2419147669DF

#include <vector>

namespace Rt
{
    namespace Algo
    {
        namespace Vector
        {
            template <class Iterator, typename T>
            void fillWithIncreasingSequence(Iterator begin, Iterator end, T min, T interval);

            template <class Iterator, typename T>
            void randomize(Iterator begin, Iterator end, T min, T max);

            template <class Iterator, typename T>
            void randomizeWithUniqueValues(Iterator begin, Iterator end, T min, T max);
        }
    }
}

#include <Runtime/Collections/VectorAlgorithmsDefinition.h>

#endif
