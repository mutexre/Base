#ifndef header_2B77D3EED399
#define header_2B77D3EED399

namespace Math
{
    namespace Geometry
    {
        namespace Hypercube
        {
            namespace Triangulated
            {
                class Topology : public Math::Geometry::Hypercube::Topology
                {
                public:
                    Topology(Rt::u1 dim);
                    virtual ~Topology() {}

                    virtual Rt::u4 getCount(Rt::u1 dim) override;
                    virtual Rt::u4 getCount(Rt::u4 id, Rt::u1 idDim, Rt::u1 elementsDim) override;
                    virtual std::vector<Rt::u4> getElements(Rt::u4 id, Rt::u1 idDim, Rt::u1 elementsDim) override;
                };
            }
        }
    }
}

#endif
