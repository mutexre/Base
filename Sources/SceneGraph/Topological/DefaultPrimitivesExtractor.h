#ifndef header_FF57E5C85A69
#define header_FF57E5C85A69

namespace SG
{
    namespace Topological
    {
        template <typename D = Rt::u1, typename I = Rt::u4>
        class DefaultPrimitivesExtractor : public React::Transform<DefaultPrimitivesExtractor<D, I>>
        {
            using Topology = std::shared_ptr<Math::Geometry::Topology<D, I>>;
            using AttributesMappingTypes = std::map<std::string, AttributesMappingType>;

            DF_IN(React::ScalarPtr<Topology>, topology, getTopology, setTopology, &DefaultPrimitivesExtractor::invalidate)
            DF_IN(React::ScalarPtr<AttributesMappingTypes>, attributesMappingTypes, getAttributesMappingTypes, setAttributesMappingTypes, &DefaultPrimitivesExtractor::invalidate)
            DF_OUT(React::ScalarPtr<std::shared_ptr<PrimitivesStream<I>>>, primitivesStream, getPrimitivesStream, setPrimitivesStream, &DefaultPrimitivesExtractor::evaluate)
            DF_OUT(React::ScalarPtr<std::shared_ptr<AttributesMapping<I>>>, attributesMappings, getAttributesMappings, setAttributesMappings, &DefaultPrimitivesExtractor::evaluate)

        private:
            D dim;

        protected:
            void invalidate() {
                if (primitivesStream.get())
                    primitivesStream->invalidate();
            }

            void evaluate() {
                auto& topology = this->topology->value();
                auto& attributesMappingsTypes = this->attributesMappingsTypes->value();
                auto& primitivesStream = this->primitivesStream->currentValue();
                auto& attributesMappings = this->attributesMappings->currentValue();

                auto& vertices = primitivesStream->getVertices();
                vertices.clear();

                attributesMappings.clear();

                auto n = topology->getCount(dim);

                switch (dim) {
                    case 0: {
                        primitivesStream.setMode(PrimitivesStream<I>::Mode::Points);
                        vertices.reserve(n);
                        for (I i = 0; i < n; i++) {
                            vertices.push_back(i);
                            
                        }
                    }
                    break;

                    case 1: {
                        primitivesStream.setMode(PrimitivesStream<I>::Mode::Lines);
                        if (topology->isElementsCountUniform(1, 0) && topology->getCount(1, 0) == 2) {
                            vertices.reserve(2 * n);
                            for (I i = 0; i < n; i++) {
                                auto e = topology->getElements(i, 1, 0);
                                vertices.push_back(e[0]);
                                vertices.push_back(e[1]);
                            }
                        }
                    }
                    break;

                    case 2: {
                        primitivesStream.setMode(PrimitivesStream<I>::Mode::Triangles);
                        if (topology->isElementsCountUniform(2, 0) && topology->getCount(2, 0) == 3) {
                            vertices.reserve(3 * n);
                            for (I i = 0; i < n; i++) {
                                auto e = topology->getElements(i, 2, 0);
                                vertices.push_back(e[0]);
                                vertices.push_back(e[1]);
                                vertices.push_back(e[2]);
                            }
                        }
                    }
                    break;
                }

                commit(this->primitivesStream);
                commit(this->attributesMappings);
            }

        public:
            DefaultPrimitivesExtractor(D dim) {
                this->dim = dim;
            }
        };
    }
}

#endif
