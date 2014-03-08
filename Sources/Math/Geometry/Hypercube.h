#ifndef header_6617611BF77E
#define header_6617611BF77E

#include <boost/bimap.hpp>
#include <Math/Internal/Geometry/Hypercube/Topology.h>

namespace Math
{
    namespace Geometry
    {
        namespace Hypercube
        {
            class Topology : public Geometry::Topology<Rt::u1, Rt::u4>
            {
            private:
                typedef boost::bimap<Rt::u4, Internal::Hypercube::Topology<Rt::u1, Rt::u4>::Id> IdsBimap;

            private:
                Rt::u1 dim;
                std::vector<IdsBimap> idsBimaps;

            public:
                Topology(Rt::u1 dim);
                virtual ~Topology() {}

                virtual Rt::u4 getCount(Rt::u1 dim) override;
                virtual Rt::u4 getCount(Rt::u4 id, Rt::u1 idDim, Rt::u1 elementsDim) override;
                virtual bool isElementsCountUniform(Rt::u1, Rt::u1 elementDim) override;
                virtual std::vector<Rt::u4> getElements(Rt::u4 id, Rt::u1 idDim, Rt::u1 elementsDim) override;
            };

            template <typename T, typename D = Rt::u1, typename I = Rt::u4>
            static std::vector<T> generateCoords(D dim) {
                I numberOfVertices = Internal::Hypercube::Topology<Rt::u1, Rt::u4>::getCount(dim, 0);
                std::vector<T> coords(numberOfVertices * dim);

                for (I vertexIndex = 0; vertexIndex < numberOfVertices; vertexIndex++)
                    for (D dimensionIndex = 0; dimensionIndex < dim; dimensionIndex++)
                        coords.data()[vertexIndex * dim + dimensionIndex] =
                            (-T(1.0) + T(2.0) * ((vertexIndex / (numberOfVertices >> (dimensionIndex + 1))) % 2));

                return coords;
            }
        }
    }
}

#endif
