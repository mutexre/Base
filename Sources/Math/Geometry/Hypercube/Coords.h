#ifndef header_9E14C7D808A0
#define header_9E14C7D808A0

namespace Math
{
    namespace Geometry
    {
        namespace Hypercube
        {
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
