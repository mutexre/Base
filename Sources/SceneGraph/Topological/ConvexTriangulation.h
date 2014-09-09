#ifndef header_FF7FF0FAF373
#define header_FF7FF0FAF373

namespace SG
{
    namespace Topological
    {
        template <typename D = Rt::u1, typename I = Rt::u4>
        class ConvexTriangulation : public React::Transform<ConvexTriangulation<D, I>>
        {
            using Topology = std::shared_ptr<Math::Geometry::Topology<D, I>>;
            using AttributesMappingTypes = std::map<std::string, AttributesMappingType>;

            REACT_DEFINE_INPUT(React::ScalarPtr<Topology>, topology, getTopology, setTopology, &ConvexTriangulation::invalidate)
            REACT_DEFINE_INPUT(React::ScalarPtr<AttributesMappingTypes>, attributesMappingTypes, getAttributesMappingTypes, setAttributesMappingTypes, &ConvexTriangulation::invalidate)
            REACT_DEFINE_OUTPUT(React::ScalarPtr<std::shared_ptr<PrimitivesStream<I>>>, primitivesStream, getPrimitivesStream, setPrimitivesStream, &ConvexTriangulation::evaluate)
            REACT_DEFINE_OUTPUT(React::ScalarPtr<std::shared_ptr<AttributesMapping<I>>>, attributesMappings, getAttributesMappings, setAttributesMappings, &ConvexTriangulation::evaluate)

        private:
            bool fan, orderedVertices;
            Rt::u4 restartIndex;

        private:
            std::vector<I> getOrderedVertices(const Topology& topology, I id) {
                auto elements = topology->getElements(id, 2, 0);
                std::vector<I> retval(elements.size());
                std::map<I, I> mapping;

                for (auto x : elements)
                    mapping[x] = topology->getElements(x, 0, 1);

                auto numberOfElementsToTraverse = elements.size() - 1;
                I currentElement = elements[0];
                I lineToFind = mapping[currentElement][0];
                retval.push_back(currentElement);

                while (numberOfElementsToTraverse > 0) {
                    for (auto& p : mapping)
                        if (currentElement != p.first) {
                            if (p.second[0] == lineToFind) {
                                currentElement = p.first;
                                lineToFind = p.second[1];
                                break;
                            }
                            else if (p.second[1] == lineToFind) {
                                currentElement = p.first;
                                lineToFind = p.second[0];
                                break;
                            }
                        }

                    retval.push_back(currentElement);

                    numberOfElementsToTraverse--;
                }

                return retval;
            }

        protected:
            void invalidate() {
                if (primitivesStream.get())
                    primitivesStream->invalidate();
            }

            void evaluate() {
                auto& topology = this->topology->get();
                auto& primitivesStream = this->primitivesStream->currentValue();

                auto& vertices = primitivesStream->getVertices();
                vertices.clear();

                auto& attributesMappings = this->attributesMappings->currentValue();
                attributesMappings.clear();

                auto& attibutesMappingsTypes = this->attributesMappingsTypes->value();

                auto numberOfPrimitives = topology->getCount(2);

                I numberOfVertices;
                if (!fan) {
                    numberOfVertices = 0;
                    for (I id = 0; id < numberOfPrimitives; id++)
                        numberOfVertices += (topology->getCount(id, 2, 0) - 2);
                    numberOfVertices *= 3;
                }
                else {
                    auto numberOfRestartIndices = numberOfPrimitives;
                    numberOfVertices = numberOfRestartIndices;
                    for (I id = 0; id < numberOfPrimitives; id++)
                        numberOfVertices += topology->getCount(id, 2, 0);
                }

                vertices.reserve(numberOfVertices);
 
                auto mode = fan ? PrimitivesStream<I>::Mode::TriangleFans : PrimitivesStream<I>::Mode::Triangles;
                primitivesStream.setMode(mode);

                if (!fan) {
                    I triangle = 0;
                    for (I id = 0; id < numberOfPrimitives; id++) {
                        auto elements = orderedVertices ? topology->getElements(id, 2, 0) : getOrderedVertices(topology, id);
                        for (I i = 2; i < elements.size(); i++) {
                            vertices.push_back(elements[0]);
                            vertices.push_back(elements[i - 1]);
                            vertices.push_back(elements[i]);

                            for (auto& p : attributesMappingsTypes)
                                switch (p.second) {
                                    case AttributesMappingType::PerVertex:
                                        attributesMapping[p.first][triangle] = id;
                                    break;

                                    case AttributesMappingType::PerPrimitive:
                                        attributesMapping[p.first][triangle] = id;
                                    break;
                                }

                            triangle++;
                        }
                    }
                }
                else
                    for (I id = 0; id < numberOfPrimitives; id++) {
                        auto elements = orderedVertices ? topology->getElements(id, 2, 0) : getOrderedVertices(topology, id);
                        for (auto id : elements)
                            vertices.push_back(id);
                        attributesMapping[id] = id;
                        vertices.push_back(restartIndex);
                    }

                commit(primitivesStream);
                commit(attributesMappings);
            }

        public:
            ConvexTriangulation(bool fan = true, bool orderedVertices = true, I restartIndex = (1 << (sizeof(I) - 1)) + 0xff) {
                this->fan = fan;
                this->orderedVertices = orderedVertices;
                this->restartIndex = restartIndex;
            }
        };
    }
}

#endif
