#ifndef header_5C6323AF2DE4
#define header_5C6323AF2DE4

namespace SG
{
    template <typename I>
    class CreateAttributesExpansionMap : public React::Transform<CreateAttributesExpansionMap<I>>
    {
        using AttributesExpansionMap = std::vector<I>;

        DF_IN(React::ScalarPtr<typename FindVertexOccurencesInPrimitivesStream<I>::Occurences>, occurences, getOccurences, setOccurences, &CreateAttributesExpansionMap::invalidate)
        DF_OUT(React::ScalarPtr<AttributesExpansionMap>, perVertexExpansionMap, getPerVertexExpansionMap, setPerVertexExpansionMap, &CreateAttributesExpansionMap::evaluate)
        DF_OUT(React::ScalarPtr<AttributesExpansionMap>, perPrimitiveExpansionMap, getPerPrimitiveExpansionMap, setPerPrimitiveExpansionMap, &CreateAttributesExpansionMap::evaluate)

    protected:
        void invalidate() {
            if (perVertexExpansionMap.get())
                perVertexExpansionMap->invalidate();

            if (perPrimitiveExpansionMap.get())
                perPrimitiveExpansionMap->invalidate();
        }

        void evaluate() {
            bool needPerVertexMap = perVertexExpansionMap.get() != nullptr;
            bool needPerPrimitiveMap = perPrimitiveExpansionMap.get() != nullptr;

            const auto& occurences = this->occurences->value();
            AttributesExpansionMap perVertex, perPrimitive;

            I i = 0;
            for (auto x : occurences) {
                auto vertex = x.first;
                const auto& occurences = x.second;

                for (auto o : occurences) {
                    perVertex.push_back(vertex);
                    perPrimitive.push_back(i);
                    i++;
                }
            }

            if (needPerVertexMap) {
                perVertexExpansionMap->set(perVertex);
                this->commit(this->perVertexExpansionMap);
            }

            if (needPerPrimitiveMap) {
                perPrimitiveExpansionMap->set(perPrimitive);
                this->commit(this->perPrimitiveExpansionMap);
            }
        }
    };
}

#endif
