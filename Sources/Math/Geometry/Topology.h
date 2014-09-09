#ifndef header_553DEF2E6A8C
#define header_553DEF2E6A8C

namespace Math
{
    namespace Geometry
    {
        template <typename D, typename I>
        class Topology
        {
        public:
            virtual ~Topology() {}

            virtual I getCount(D) = 0;
            virtual I getCount(I id, D idDim, D) = 0;
            virtual I getCount(D, D elementDim) = 0; // returned value is undefined in case elements count is non-uniform
            virtual bool isElementsCountUniform(D, D) = 0;
            virtual std::vector<I> getElements(I id, D idDim, D) = 0;
        };
    }
}

#endif
