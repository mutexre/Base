#ifndef header_5015EF6C1737
#define header_5015EF6C1737

namespace SG
{
    template <typename I>
    class AreTherePerVertexOrPerPrimitiveAttributes : public React::Transform<AreTherePerVertexOrPerPrimitiveAttributes<I>>
    {
        using AttributesMappingTypes = std::map<std::string, AttributeMappingType>;

        DF_IN(React::ScalarPtr<AttributesMappingTypes>, attributesMappingTypes, getAttributesMappingTypes, setAttributesMappingTypes, &AreTherePerVertexOrPerPrimitiveAttributes::invalidate)
        DF_OUT(React::ScalarPtr<bool>, hasPerVertexAttributes, getHasPerVertexAttributes, setHasPerVertexAttributes, &AreTherePerVertexOrPerPrimitiveAttributes::evaluate)
        DF_OUT(React::ScalarPtr<bool>, hasPerPrimitiveAttributes, getHasPerPrimitiveAttributes, setHasPerPrimitiveAttributes, &AreTherePerVertexOrPerPrimitiveAttributes::evaluate)

    protected:
        void invalidate() {
            if (hasPerVertexAttributes.get())
                hasPerVertexAttributes->invalidate();

            if (hasPerPrimitiveAttributes.get())
                hasPerPrimitiveAttributes->invalidate();
        }

        void evaluate() {
            auto& mappingTypes = attributesMappingTypes->value();
            bool hasPerVertex, hasPerPrimitive;

            hasPerVertex = hasPerPrimitive = false;

            for (auto attr : mappingTypes) {
                if (attr.second == AttributeMappingType::PerVertex)
                    hasPerVertex = true;
                else if (attr.second == AttributeMappingType::PerPrimitive)
                    hasPerPrimitive = true;

                if (hasPerVertex && hasPerPrimitive) break;
            }

            hasPerVertexAttributes->set(hasPerVertex);
            hasPerPrimitiveAttributes->set(hasPerPrimitive);

            this->commit(this->hasPerVertexAttributes);
            this->commit(this->hasPerPrimitiveAttributes);
        }
    };
}

#endif
