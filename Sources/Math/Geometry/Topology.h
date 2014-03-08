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
            virtual I getCount(I, D, D) = 0;
            virtual bool isElementsCountUniform(D, D elementDim) = 0;
            virtual std::vector<I> getElements(I, D, D) = 0;
        };
    }
}

#endif
