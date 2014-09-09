#ifndef header_F2401FC7AD32
#define header_F2401FC7AD32

namespace SG
{
    namespace Topological
    {
        struct Parameters {
            React::ScalarPtr<std::shared_ptr<SG::Program>> program;
            React::ScalarPtr<std::shared_ptr<SG::Material>> material;
            React::ScalarPtr<bool> enableColorArray;
            React::ScalarPtr<bool> enableDepthTest;
            React::ScalarPtr<Color::RGBA<float>> color;
        };

        template <typename D = Rt::u1, typename I = Rt::u4>
        class Cpu2GpuProjection : public React::Transform<Cpu2GpuProjection<D, I>>
        {
            REACT_DEFINE_INPUT(React::ScalarPtr<PrimitivesStream<I>>, primitivesStream, getPrimitivesStream, setPrimitivesStream, &Cpu2GpuProjection::invalidate)
            REACT_DEFINE_INPUT(React::ScalarPtr<Attributes>, attrs, getAttrs, setAttrs, &Cpu2GpuProjection::invalidate)
            REACT_DEFINE_OUTPUT(React::ScalarPtr<std::shared_ptr<SG::Data>>, data, getData, setData, &Cpu2GpuProjection::evaluate)
            REACT_DEFINE_OUTPUT(React::ScalarPtr<std::shared_ptr<SG::DrawCall>>, drawCall, getDrawCall, setDrawCall, &Cpu2GpuProjection::evaluate)

        private:
            D dim;
            bool interleaved;
            Rt::Option<Rt::u2> rounding;

            struct {
                std::vector<Rt::u1> verticesData;
                std::vector<Rt::u4> primitivesVertices;

                bool isNumberOfPrimitivesPerVerticesUniform;
                I numberOfPrimitivesPerVertices;
                std::vector<I> numbersOfPrimitivesPerVertices;

                bool isNumberOfVerticesPerPrimitiveUniform;
                I numberOfVerticesPerPrimitives;
                std::vector<I> numbersOfVerticesPerPrimitives;

                std::vector<I> verticesUsed;
                I verticesUsedCount, primitivesCount;
                I totalNumberOfVerticesCopies;
                std::map<I, I> verticesIndices;
                std::vector<I> verticesOffsets;

                std::map<std::string, Rt::u4> dstAttrOffsets, dstAttrStrides;
                Rt::u4 dataSizePerVertex;
                Rt::u4 dataSize;
                std::vector<I> primitivesVerticesOffsets;

                std::shared_ptr<GL::Buffer> arrayBuffer;
            }
            vault;

/*            std::set<I> findVerticesUsed(const Math::Geometry::Topology<D, I>& topology) {
                std::set<I> vertices;
                I primitivesCount = topology->getCount(dim);
                for (I i = 0; i < primitivesCount; i++) {
                    auto elements = topology->getElements(i, dim, 0);
                    for (I e : elements) vertices.insert(e);
                }
                return vertices;
            }

            template <typename VertexIterator>
            std::map<I, I> calcVerticesIndices(VertexIterator first, VertexIterator last) {
                std::map<I, I> verticesIndices;
                for (I i = 0; first != last; ++first, i++)
                    verticesIndices[*first] = i;
                return verticesIndices;
            }

            template <typename VertexIterator, typename OutputIterator>
            OutputIterator calcNumbersOfPrimitivesPerVertices(VertexIterator first, VertexIterator last, OutputIterator output) {
                for (; first != last; ++first, ++output) {
                    I vertex = *first;
                    *output = topology->getCount(vertex, 0, dim);
                }
                return output;
            }

            template <typename OutputIterator>
            OutputIterator calcNumbersOfElementsPerElements(I start, I count, D idDim, D dim, OutputIterator output) {
                for (I id = start; id < start + count; id++)
                    *output = topology->getCount(id, idDim, dim);

                return output;
            }

            template <typename VertexIterator, typename OutputIterator>
            OutputIterator calcOffsets(VertexIterator first, VertexIterator last, OutputIterator output) {
                *output = 0; output++;
                std::partial_sum(first, last, output, [](I accum, I x) -> I {
                    return accum + std::max<I>(x, 1);
                });
            }*/

            template <typename T>
            T round(T x, T rounding) {
                return rounding * ((x - T(1)) / rounding + T(1));
            }

            template <typename T>
            T roundIfNeeded(T x) {
                if (rounding.defined)
                    return round(x, rounding.value);
                return x;
            }

            void managePrimitivesData() {
                if (dim > 0) {
                    auto& topologyVal = topology->value();
                    std::set<I> setOfUsedVertices = findVerticesUsed(topologyVal);
                    std::copy(setOfUsedVertices.begin(), setOfUsedVertices.end(), std::back_inserter(vault.verticesUsed));

                    vault.primitivesCount = topologyVal->getCount(dim);
                    vault.isNumberOfPrimitivesPerVerticesUniform = topologyVal.isElementsCountUniform(0, dim);
                    vault.isNumberOfVerticesPerPrimitiveUniform = topologyVal.isElementsCountUniform(dim, 0);
                    vault.verticesUsedCount = vault.verticesUsed.size();
                    vault.verticesIndices = calcVerticesIndices(vault.verticesUsed.begin(), vault.verticesUsed.end());
                    vault.verticesOffsets.reserve(vault.verticesUsedCount);

                    if (!vault.isNumberOfPrimitivesPerVerticesUniform) {
                        calcNumbersOfPrimitivesPerVertices(vault.verticesUsed.begin(), vault.verticesUsed.end(), vault.numbersOfPrimitivesPerVertices.begin());
                        calcOffsets(vault.numbersOfPrimitivesPerVertices.begin(), vault.numbersOfPrimitivesPerVertices.end(), vault.verticesOffsets.begin());
                        vault.totalNumberOfVerticesCopies = vault.verticesOffsets[vault.verticesOffsets.size() - 1] +
                                                            vault.numbersOfPrimitivesPerVertices[vault.numbersOfPrimitivesPerVertices.size() - 1];
                    }
                    else {
                        vault.numberOfPrimitivesPerVertex = topology->getCount(dim, 0);
                        for (int i = 0; i < vault.verticesUsedCount; i++)
                            vault.verticesOffsets[i] = i * vault.numberOfPrimitivesPerVertex;
                        vault.totalNumberOfVerticesCopies = vault.verticesUsedCount * vault.numberOfPrimitivesPerVertex;
                    }

                    if (!vault.isNumberOfVerticesPerPrimitivesUniform) {
                        calcNumbersOfElementsPerElements(0, vault.primitivesCount, dim, vault.numbersOfVerticesPerPrimitives.begin());
                        calcOffsets(vault.numbersOfVerticesPerPrimitives.begin(), vault.numbersOfVerticesPerPrimitives.end(), vault.primitivesVerticesOffsets.begin());
                        vault.totalNumberOfPrimitivesVertices = vault.primitivesVerticesOffsets[vault.primitivesVerticesOffsets.size() - 1] +
                                                                vault.numbersOfVerticesPerPrimitives[vault.numbersOfVerticesPerPrimitives.size() - 1];
                    }
                    else {
                        vault.numberOfVerticesPerPrimitives = topology->getCount(0, dim);
                        for (int primitive = 0; primitive < vault.primitivesCount; primitive++)
                            vault.primitivesVerticesOffsets[primitive] = primitive * vault.numberOfVerticesPerPrimitives;
                        vault.totalNumberOfPrimitivesVertices = vault.primitivesCount * vault.numberOfVerticesPerPrimitives;
                    }

                    vault.primitivesVertices.reserve(vault.totalNumberOfPrimitivesVertices);

                    std::vector<I> counters(vault.verticesUsedCount);
                    std::fill_n(counters.begin(), vault.verticesUsedCount, 0);

                    for (I primitive = 0; primitive < vault.primitivesCount; primitive++) {
                        auto vertices = topology->getElements(primitive, dim, 0);
                        auto verticesOffset = vault.primitivesVerticesOffsets[primitive];
                        auto numberOfVerticesPerPrimitive = vault.isNumberOfVerticesPerPrimitivesUniform ? vault.numberOfVerticesPerPrimitive :
                                                                                                           vault.numbersOfVerticesPerPrimitives[primitive];
                        for (I vertex = 0; vertex < numberOfVerticesPerPrimitive; vertex++) {
                            I vertexIndex = vault.verticesIndices[vertices[vertex]];
                            vault.primitivesVertices[verticesOffset + vertex] = vault.verticesOffsets[vertexIndex] + counters[vertexIndex];
                            counters[vertexIndex]++;
                        }
                    }

                    auto elementBuffer = std::make_shared<GL::Buffer>();
                    GL::Buffer::bind(GL::Buffer::Target::ElementArray, *elementBuffer);
                    GL::Buffer::data(GL::Buffer::Target::ElementArray,
                                     vault.totalNumberOfPrimitivesVertices * sizeof(GLuint),
                                     vault.primitivesVertices.data(),
                                     GL::Buffer::Usage::StaticDraw);

                    GLenum mode;
                    switch (dim) {
                        case 1: mode = GL_LINES; break;
                        case 2: mode = GL_TRIANGLES; break;
                        default: Rt::error(0x826709CF);
                    }

                    drawCall->currentValue()->init(mode,
                                                   GL::verticesPerEdge * vault.primitivesCountj,
                                                   GL_UNSIGNED_INT,
                                                   data->getEdgesOffset());
                }
                else
                    vault.totalNumberOfVerticesCopies = vault.primitivesCount;
            }

            void calcInterleavedAttrsOffsetsAndDataSizePerVertex(const Attributes& attrs) {
                vault.dataSizePerVertex = 0;

                for (auto& pair : attrs) {
                    auto& name = pair.first;
                    auto& attr = pair.second;

                    vault.dstAttrOffsets[name] = vault.dataSizePerVertex;
                    vault.dataSizePerVertex += roundIfNeeded(attr.layout.size * GL::getSizeOfType(attr.layout.type));
                }
            }

            void setupInterleavedAttributes(const Attributes& attrs) {
                for (auto& pair : attrs) {
                    auto& name = pair.first;
                    auto& attr = pair.second;
                    auto layout = attr.layout;

                    layout.stride = vault.dstAttrStrides[name] = vault.dataSizePerVertex;
                    layout.offset = vault.dstAttrOffsets[name];
                    data->currentValue()->setAttr(name, vault.arrayBuffer, layout);
                }
            }

            void setupSeparateAttributes(const Attributes& attrs) {
                Rt::u4 offset = 0;

                for (auto& pair : attrs) {
                    auto& name = pair.first;
                    auto& attr = pair.second;
                    auto layout = attr.layout;

                    layout.stride = vault.dstAttrStrides[name] = roundIfNeeded(attr.layout.size * GL::getSizeOfType(attr.layout.type));
                    layout.offset = vault.dstAttrOffsets[name] = offset;
                    data->currentValue()->setAttr(name, vault.arrayBuffer, layout);

                    offset += roundIfNeeded(layout.stride * vault.totalNumberOfVerticesCopies);
                }

                vault.dataSize = offset;
            }

            void manageVerticesData() {
                vault.arrayBuffer = std::make_shared<GL::Buffer>();
                GL::Buffer::bind(GL::Buffer::Target::Array, *vault.arrayBuffer);

                data->currentValue()->clearAttrs();

                auto& attrsVal = attrs->value();
                if (interleaved) {
                    calcInterleavedAttrsOffsetsAndDataSizePerVertex(attrsVal);
                    setupInterleavedAttributes(attrsVal);
                    vault.dataSize = vault.dataSizePerVertex * vault.totalNumberOfVerticesCopies;
                }
                else
                    setupSeparateAttributes(attrsVal);

                vault.arrays.reserve(vault.dataSize);
                GL::Buffer::data(GL::Buffer::Target::Array, vault.dataSize, 0, GL::Buffer::Usage::DynamicDraw);
            }

            void printVaultVariables() {
/*                std::vector<Rt::u1> verticesData;
                std::vector<Rt::u4> primitivesVertices;

                std::vector<I> verticesUsed;
                I verticesUsedCount, primitivesCount;

                bool isNumberOfPrimitivesPerVerticesUniform;
                I numberOfPrimitivesPerVertices;
                std::vector<I> numbersOfPrimitivesPerVertices;

                bool isNumberOfVerticesPerPrimitiveUniform;
                I numberOfVerticesPerPrimitives;
                std::vector<I> numbersOfVerticesPerPrimitives;

                I totalNumberOfVerticesCopies;
                std::map<I, I> verticesIndices;
                std::vector<I> verticesOffsets;

                std::map<std::string, Rt::u4> dstAttrOffsets, dstAttrStrides;
                Rt::u4 dataSizePerVertex;
                Rt::u4 dataSize;
                std::vector<I> primitivesVerticesOffsets;

                std::shared_ptr<GL::Buffer> arrayBuffer;*/

                printf("Primitives count: %u\n", vault.primitivesCount);
                printf("Vertices used: %u\n", vault.verticesUsedCount);

                printf("Number of primitives per vertices is uniform: %s\n", vault.isNumberOfPrimitivesPerVerticesUniform ? "true" : "false");
                if (vault.isNumberOfPrimitivesPerVerticesUniform)
                    printf("Number of primitives per vertices: %u\n", vault.numberOfPrimitivesPerVertices);
                else {
                    printf("Numbers of primitives per vertices: ");
                    for (I x : vault.numbersOfPrimitivesPerVertices)
                        printf("%u ", x);
                    printf("\n");
                }

                printf("Number of vertices per primitives is uniform: %s\n", vault.isNumberOfVerticesPerPrimitiveUniform ? "true" : "false");
                if (vault.isNumberOfPrimitivesPerVerticesUniform)
                    printf("Number of primitives per vertices: %u\n", vault.numberOfPrimitivesPerVertices);
                else {
                    printf("Numbers of primitives per vertices: ");
                    for (I x : vault.numbersOfVerticesPerPrimitives)
                        printf("%u ", x);
                    printf("\n");
                }

                printf("Data size per vertex: %u\n", vault.dataSizePerVertex);
                printf("Vertices data size: %u\n", vault.dataSize);
                printf("Total number of vertices per all primitives: %u\n", vault.totalNumberOfVerticesCopies);

                printf("Destination attributes offsets:");
                for (auto p : vault.dstAttrOffsets)
                    printf("%s -> %u ", p.first.c_str(), p.second);
                printf("\n");

                printf("Destination attributes strides:");
                for (auto p : vault.dstAttrStrides)
                    printf("%s -> %u ", p.first.c_str(), p.second);
                printf("\n");
            }

            void handlePrimitivesStreamChange() {
                managePrimitivesData();
                manageVerticesData();
                printVaultVariables();
            }

            void copyData() {
                auto& attrsVal = attrs->value();

                if (dim > 0) {
                    for (auto& pair : attrsVal) {
                        auto& name = pair.first;
                        auto& attr = pair.second;
                        auto size = attr.layout.size * GL::getSizeOfType(attr.layout.type);

                        if (attr.perVertex)
                            for (auto vertex : vault.verticesUsed) {
                                auto vertexIndex = vault.verticesIndices[vertex];
                                auto vertexOffset = vault.verticesOffsets[vertexIndex];
                                auto numberOfPrimitivesPerVertex = vault.isNumberOfPrimitivesPerVerticesUniform ? vault.numberOfPrimitivesPerVertices :
                                                                                                                  vault.numbersOfPrimitivesPerVertices[vertexIndex];

                                for (auto copyIndex = 0; copyIndex < numberOfPrimitivesPerVertex; copyIndex++)
                                    memcpy(vault.arrays.data() + vault.dstAttrOffsets[name] + vault.dstAttrStrides[name] * (vertexOffset + copyIndex),
                                           static_cast<Rt::u1*>(attr.ptr) + attr.layout.offset + attr.layout.stride * vertex,
                                           size);
                            }
                        else
                            for (I primitive = 0; primitive < vault.primitivesCount; primitive++) {
                                auto verticesOffset = vault.primitivesVerticesOffsets[primitive];
                                auto numberOfVerticesPerPrimitive = vault.isNumberOfVerticesPerPrimitivesUniform ? vault.numberOfVerticesPerPrimitives :
                                                                                                                   vault.numbersOfVerticesPerPrimitives[primitive];

                                for (auto vertex = 0; vertex < numberOfVerticesPerPrimitive; vertex++) {
                                    auto vertexIndex = vault.primitivesVertices[verticesOffset + vertex];
                                    memcpy(vault.arrays.data() + vault.dstAttrOffsets[name] + vault.dstAttrStrides[name] * vertexIndex,
                                           static_cast<Rt::u1*>(attr.ptr) + attr.layout.offset + attr.layout.stride * primitive,
                                           size);
                                }
                            }
                    }
                }
                else
                    for (auto& pair : attrsVal) {
                        auto& name = pair.first;
                        auto& attr = pair.second;
                        Rt::stridedCopy(attr.ptr, attr.layout.stride,
                                        vault.arrays.data() + vault.attrOffsets[name], vault.attrStrides[name],
                                        vault.primitivesCount);
                    }

                GL::Buffer::bind(GL::Buffer::Target::Array, vault.arrayBuffer);
                GL::Buffer::subData(GL::Buffer::Target::Array, 0, vault.dataSize, vault.arrays.data());
            }

        protected:
            void evaluate() {
                if (this->isChanged(primitivesStream))
                    handlePrimitivesStreamChange();

                if (this->isChanged(attrs) || this->isChanged(primitivesStream))
                    copyData();

                this->commit(data);
                this->commit(drawCall);
            }

            void invalidate() {
                if (data.get())
                    data->invalidate();

                if (drawCall.get())
                    drawCall->invalidate();
            }

        public:
            Cpu2GpuProjection(D dim, bool interleaved = true, Rt::Option<Rt::u2> rounding = Rt::Option<Rt::u2>()) {
                this->dim = dim;
                this->interleaved = interleaved;
                this->rounding = rounding;
            }
        };
    }
}

#endif
