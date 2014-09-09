#ifndef header_AF453430FE6D
#define header_AF453430FE6D

namespace Math
{
    namespace Geometry
    {
        namespace Hypercube
        {
            namespace Triangulated
            {
                class SourceElementsProvider : public Math::Geometry::SourceElementsProvider<Rt::u1, Rt::u4>
                {
                public:
                    SourceElementsProvider(Rt::u1 dim);
                    virtual ~SourceElementsProvider() {}

                    virtual Rt::u4 getSourceElement(Rt::u1, Rt::u4) override;
                    virtual std::vector<Rt::u4> getSourceElements(Rt::u1) override;
                };
            }
        }
    }
}

#endif
