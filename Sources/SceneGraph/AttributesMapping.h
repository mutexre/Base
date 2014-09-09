#ifndef header_15731701810B
#define header_15731701810B

namespace SG
{
    enum class AttributesMappingType {
        PerVertex,
        PerPrimitive
    };

    template <typename I>
    using AttributesMapping = std::map<std::string, std::vector<I>>;
}

#endif