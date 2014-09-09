#include <Math/Math.h>

Math::Geometry::Hypercube::Triangulated::Topology::Topology(Rt::u1 dim) : Math::Geometry::Hypercube::Topology(dim)
{}

Rt::u4 Math::Geometry::Hypercube::Triangulated::Topology::getCount(Rt::u1 dim) {
    if (dim <= 2) {
        auto n = Math::Hypercube::Topology<Rt::u1, Rt::u4>::getCount(dim);
        return (dim == 2) ? 2 * n : n;
    }
    return 0;
}

Rt::u4 Math::Geometry::Hypercube::Triangulated::Topology::getCount(Rt::u4 id, Rt::u1 idDim, Rt::u1 elementsDim) {
    if (idDim > 2 || elementsDim > 2) return 0;
    if (idDim == 2 && elementsDim < 2) return 3;
    if (idDim == 0 && elementsDim == 2) return ?;
    return Math::Hypercube::Topology<Rt::u1, Rt::u4>::getCount(id, idDim, elementsDim);
}

std::vector<Rt::u4> Math::Geometry::Triangulated::Hypercube::Topology::getElements(Rt::u4 id, Rt::u1 idDim, Rt::u1 elementsDim) {
    std::vector<Rt::u4> retval;
    auto elements = Internal::Hypercube::Topology<Rt::u1, Rt::u4>::getElements(dim, idsBimaps[idDim].left.at(id), elementsDim);
    for (auto& x : elements) retval.push_back(idsBimaps[elementsDim].right.at(x));
    return retval;
}
