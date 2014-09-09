#ifndef header_98DCFF201EC4
#define header_98DCFF201EC4

namespace SG
{
    class TriangleMesh
    {
        template <typename D, typename I>
        class TriangleMesh
        {
        public:
            virtual ~TriangleMesh() {}

            virtual I getCount(D) = 0;
            virtual I getCount(I id, D idDim, D) = 0;
            virtual std::vector<I> getElements(I id, D idDim, D) = 0;
        };
    };
}

#endif
