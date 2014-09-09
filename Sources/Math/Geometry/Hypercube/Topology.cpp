#include <Math/Math.h>

Math::Geometry::Hypercube::Topology::Topology(Rt::u1 dim) {
    this->dim = dim;
    idsBimaps.reserve(dim + 1);
    for (auto i = 0; i <= dim; i++)
    {
        idsBimaps.push_back(IdsBimap());
        auto elements = Internal::Hypercube::Topology<Rt::u1, Rt::u4>::getElements(dim, i);
        for (auto j = 0; j < elements.size(); j++) {
            auto internalId = elements[j];
            idsBimaps[i].left.insert(IdsBimap::left_value_type(j, internalId));
        }
    }
}

Rt::u4 Math::Geometry::Hypercube::Topology::getCount(Rt::u1 dim) {
    return Internal::Hypercube::Topology<Rt::u1, Rt::u4>::getCount(this->dim, dim);
}

Rt::u4 Math::Geometry::Hypercube::Topology::getCount(Rt::u4 id, Rt::u1 idDim, Rt::u1 elementsDim) {
    return Internal::Hypercube::Topology<Rt::u1, Rt::u4>::getCount(dim, idsBimaps[idDim].left.at(id), elementsDim);
}

bool Math::Geometry::Hypercube::Topology::isElementsCountUniform(Rt::u1 dim, Rt::u1 elementsDim) {
    return true;
}

std::vector<Rt::u4> Math::Geometry::Hypercube::Topology::getElements(Rt::u4 id, Rt::u1 idDim, Rt::u1 elementsDim) {
    std::vector<Rt::u4> retval;
    auto elements = Internal::Hypercube::Topology<Rt::u1, Rt::u4>::getElements(dim, idsBimaps[idDim].left.at(id), elementsDim);
    for (auto& x : elements) retval.push_back(idsBimaps[elementsDim].right.at(x));
    return retval;
}
