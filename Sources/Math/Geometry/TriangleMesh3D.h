#ifndef header_B264F39C9DF2
#define header_B264F39C9DF2

namespace Math
{
    namespace Geometry
    {
        template <typename I>
        class Mesh
        {
        public:
#if 0
            virtual I getCount0() = 0;
            virtual I getCount1() = 0;
            virtual I getCount2() = 0;

            virtual I getCount10(I) = 0;
            virtual I getCount20(I) = 0;

            virtual bool isCountUniform10() = 0;
            virtual bool isCountUniform20() = 0;

            virtual Edge<I> getElements01(I) = 0;
            virtual Triangle<I> getElements02(I) = 0;

            virtual std::vector<Edge<I>> getAllElements01(I) = 0;
            virtual std::vector<Triangle<I>> getAllElements02(I) = 0;
#else
            virtual I getCount(Rt::u1 dim) = 0;
            virtual I getCount(Rt::u1 dim, I id) = 0;
            virtual bool isCountUniform(Rt::u1 dim) = 0;

            virtual std::vector<I> getVertices(Rt::u1 dim, I id) = 0;
            virtual Triangle<I> getVertices(Rt::u1 dim, I id) = 0;

            virtual Edge<I> getEdge(I) = 0;
            virtual Triangle<I> getTriangle(I) = 0;

            virtual std::vector<Edge<I>> getEdges(I) = 0;
            virtual std::vector<Triangle<I>> getTriangles(I) = 0;
#endif
        };
    }
}

#endif
