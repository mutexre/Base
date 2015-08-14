#ifndef header_15731701810B
#define header_15731701810B

namespace SG
{
    template <typename I>
    struct AttributeMapping
    {
    public:
        enum class Type {
            PerVertex,
            PerPrimitive
        };

        using Mapping = std::vector<I>;

    public:
        Type type;
        Mapping mapping;

    public:
        AttributeMapping() {}

        AttributeMapping(Type type, Mapping mapping) {
            this->type = type;
            this->mapping = mapping;
        }
    };

    template <typename I>
    using AttributesMapping = std::map<std::string, AttributeMapping<I>>;
}

#endif
