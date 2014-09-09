#ifndef header_E3A34EB3A6F9
#define header_E3A34EB3A6F9

#include <vector>

#include <Runtime/Runtime.h>

namespace Math
{
    template <typename N, typename T> T powOf2(N n);

    template <typename N, typename T>
    T calcNumberOfCombinations(N numberOfSlots, N numberOfThings);

    template <typename T>
    T nextPermutationInLexicographicalOrder(T permutation);

    template <typename T, typename D = Rt::u1, typename I = Rt::u4>
    std::vector<T> calcCenterOfMass(const std::vector<T>&, D dim, I count);

    template <typename T, typename D = Rt::u1, typename I = Rt::u4>
    T calcMaxDistFromPoint(const std::vector<T>&, D dim, I count, const std::vector<T>& point);

    template <typename T = float>
    void normalize(std::vector<T>&, T value);
}

#if defined _WIN32 || defined _WIN64
    #include <intrin.h>
#endif

#ifndef M_PI
    #define M_PI 3.141592654
#endif

#include <Math/Rational.h>

#include <Math/Vector.h>
#include <Math/Vertex.h>
#include <Math/VectorDefinition.h>
#include <Math/VertexDefinition.h>
#include <Math/Plane.h>
#include <Math/RotationInPlane.h>

#include <Math/Matrix/Matrix.h>
#include <Math/Matrix/Scale.h>
#include <Math/Matrix/Translation.h>
#include <Math/Matrix/Rotation.h>
#include <Math/Matrix/OrthogonalProjection.h>
#include <Math/Matrix/PerspectiveProjection.h>

/*
#include <Math/Transformations/Transformation.h>
#include <Math/Transformations/Vertex/VertexTransformation.h>
#include <Math/Transformations/Vector/VectorTransformation.h>
#include <Math/Transformations/Plane/PlaneTransformation.h>
#include <Math/Transformations/Matrix/Matrix.h>
#include <Math/Transformations/Matrix/Square/SquareMatrix.h>
#include <Math/Transformations/Matrix/Square/SquareMatrix2.h>
#include <Math/Transformations/Matrix/Square/SquareMatrix3.h>
#include <Math/Transformations/Matrix/Square/SquareMatrix4.h>
#include <Math/Transformations/Matrix/Square/Vertex/VertexMatrixTransformation.h>
#include <Math/Transformations/Matrix/Square/Vertex/Special/Rotation.h>
#include <Math/Transformations/Matrix/Square/Vertex/Special/Scale.h>
#include <Math/Transformations/Matrix/Square/Vertex/Special/Translation.h>
#include <Math/Transformations/Matrix/Square/Vertex/Special/PerspectiveProjection.h>
#include <Math/Transformations/Matrix/Square/Vertex/Special/Combinations/SP.h>
#include <Math/Transformations/Matrix/Square/Vertex/Special/Combinations/TSP.h>
*/
#include <Math/Distribution/Trait.h>
#include <Math/Distribution/Bounded.h>
#include <Math/Distribution/Unbounded.h>
#include <Math/Distribution/Uniform.h>
#include <Math/Distribution/Degenerate.h>
#include <Math/Distribution/Transformation.h>

#include <Math/Geometry/Topology.h>
#include <Math/Geometry/SourceElementsProvider.h>
#include <Math/Geometry/MixedCoordinates.h>
#include <Math/Geometry/Primitives.h>
#include <Math/Geometry/Ring.h>
#include <Math/Geometry/PolarRose.h>
//#include <Math/Geometry/TriangleMesh3D.h>

#include <Math/Geometry/Hypercube/Topology.h>
#include <Math/Geometry/Hypercube/Coords.h>
#include <Math/Geometry/Hypercube/Triangulated/Topology.h>
#include <Math/Geometry/Hypercube/Triangulated/SourceElementsProvider.h>

namespace Math {
    #include <Math/MathDefinition.h>
}

#endif
