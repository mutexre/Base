#ifndef header_EFB1C5B8049A
#define header_EFB1C5B8049A

namespace SG
{
    template <typename I>
    using AttributesExpansionMap = std::map<std::string, std::vector<std::vector<I>>>;

    template <typename I>
    class CalcAttributesExpansionMap : public React::Transform<CalcAttributesExpansionMap<I>>
    {
        REACT_DEFINE_INPUT(React::ScalarPtr<PrimitivesStream<I>>, primitivesStream, getPrimitivesStream, setPrimitivesStream, &CalcAttributesExpansionMap::invalidate)
        REACT_DEFINE_INPUT(React::ScalarPtr<AttributesMapping<I>>, attributesMappings, getAttributesMappings, setAttributesMappings, &CalcAttributesExpansionMap::invalidate)
        REACT_DEFINE_OUTPUT(React::ScalarPtr<AttributesExpansionMap<I>>, attributesExpansionMap, getAttributesExpansionMap, setAttributesExpansionMap, &CalcAttributesExpansionMap::evaluate)

    protected:
        void invalidate() {
            if (attributesExpansionMap.get())
                attributesExpansionMap->invalidate();
        }

        void evaluate() {
            this->commit(this->attributesExpansionMap);
        }
    };

    template <typename I>
    class AttributesExpander : public React::Transform<AttributesExpander<I>>
    {
        using AttributesData = std::map<std::string, void*>;
        using AttributesLayout = std::map<std::string, GL::VertexArray::AttribPointer>;

        REACT_DEFINE_INPUT(React::ScalarPtr<PrimitivesStream<I>>, primitivesStream, getPrimitivesStream, setPrimitivesStream, &AttributesExpander::invalidatePrimitivesStream)
        REACT_DEFINE_INPUT(React::ScalarPtr<AttributesData>, attributesData, getAttributesData, setAttributesData, &AttributesExpander::invalidateAttributesData)
        REACT_DEFINE_INPUT(React::ScalarPtr<AttributesLayout>, attributesLayout, getAttributesLayout, setAttributesLayout, &AttributesExpander::invalidateAttributesLayout)
        REACT_DEFINE_INPUT(React::ScalarPtr<AttributesMapping<I>>, attributesMappings, getAttributesMappings, setAttributesMappings, &AttributesExpander::invalidateAttributesMappings)
        REACT_DEFINE_OUTPUT(React::ScalarPtr<PrimitivesStream<I>>, expandedPrimitivesStream, getExpandedPrimitivesStream, setExpandedPrimitivesStream, &AttributesExpander::evaluateExpandedPrimitivesStream)
        REACT_DEFINE_OUTPUT(React::ScalarPtr<AttributesData>, expandedAttributesData, getExpandedAttributesData, setExpandedAttributesData, &AttributesExpander::evaluateExpandedAttributes)

    private:
        React::ScalarPtr<AttributesExpansionMap<I>> attributesExpansionMap;
        std::unique_ptr<CalcAttributesExpansionMap<I>> calcAttributesExpansionMap;

    protected:
        void invalidatePrimitivesStream() {
            if (expandedPrimitivesStream.get())
                expandedPrimitivesStream->invalidate();

            if (attributesExpansionMap.get())
                attributesExpansionMap->invalidate();
        }

        void invalidateAttributes() {
            if (expandedAttributes.get())
                expandedAttributes->invalidate();
        }

        void invalidateAttributesMappings() {
            if (expandedPrimitivesStream.get())
                expandedPrimitivesStream->invalidate();
        }

        void evaluateExpandedPrimitivesStream() {
            
            this->commit(this->expandedPrimitivesStream);
        }

        void evaluateExpandedAttributes() {
            
            this->commit(this->expandedAttributes);
        }

    public:
        AttributesExpander() {
            attributesExpansionMap = React::makeScalarPtr<AttributesExpansionMap<I>>();

            calcAttributesExpansionMap = std::unique_ptr<CalcAttributesExpansionMap<I>>(new CalcAttributesExpansionMap<I>());
            calcAttributesExpansionMap->setPrimitivesStream(primitivesStream);
            calcAttributesExpansionMap->setAttributesMappings(attributesMappings);
            calcAttributesExpansionMap->setAttributesExpansionMap(attributesExpansionMap);
        }

        virtual ~AttributesExpander() {}
    };
}

#endif
