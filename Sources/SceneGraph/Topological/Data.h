#ifndef header_8AA4D5118001
#define header_8AA4D5118001

namespace SG
{
    namespace Topological
    {
        template <typename D = Rt::u1, typename I = Rt::u4>
        class Data : public SG::Data
        {
        public:
            using Rotations = std::vector<Math::RotationInPlane<>>;

        private:
            D dim;
            std::vector<float> coords;
            I numberOfVertices, numberOfEdges, numberOfQuads;

            bool isNumberOfEdgesPerVertexUniform;
            bool isNumberOfQuadsPerVertexUniform;
            I numberOfEdgesPerVertex;
            I numberOfQuadsPerVertex;

            std::vector<I> edgesPerVertex;
            std::vector<I> quadsPerVertex;
            std::vector<I> vertexOffsets;

            I totalNumberOfVertices;

            std::shared_ptr<Math::Geometry::Topology<D, I>> topology;

            struct DataSize {
                Rt::u4 coords, normals, colors, d0, d1, d2, whole;
            }
            dataSize;

            struct {
                Rt::u4 coords, normals, colors, d0, d1, d2;
            }
            dataOffset;

            struct {
                std::vector<Math::Vector<float>> coords, normals;
                std::vector<Color::RGBA<float>> colors;
                std::vector<I> d0;
                std::vector<Math::Geometry::Edge<I>> d1;
                std::vector<Math::Geometry::Triangle<I>> d2;
            }
            data;

            std::shared_ptr<GL::Buffer> buffer;

        private:
            void initVerticesEdges() {
                if (isNumberOfEdgesPerVertexUniform)
                    numberOfEdgesPerVertex = topology->getCount(0, 0, 1);
                else
                    for (I vertex = 0; vertex < numberOfVertices; vertex++)
                        edgesPerVertex.push_back(topology->getCount(vertex, 0, 1));
            }

            void initVerticesQuads() {
                if (isNumberOfQuadsPerVertexUniform)
                    numberOfQuadsPerVertex = topology->getCount(0, 0, 2);
                else
                    for (I vertex = 0; vertex < numberOfVertices; vertex++)
                        quadsPerVertex.push_back(topology->getCount(vertex, 0, 2));
            }

            void calcVerticesOffsets() {
                if (!isNumberOfQuadsPerVertexUniform) {
                    vertexOffsets.push_back(0);
                    std::partial_sum(quadsPerVertex.begin(), quadsPerVertex.end(), vertexOffsets.begin() + 1, [](I accum, I x) -> I {
                        return accum + std::max<I>(x, 1);
                    });

                    printf("vertexOffset size = %lu\n", vertexOffsets.size());
                    for (auto n : vertexOffsets)
                        printf(" %u", n);
                    printf("\n");
                }
            }

            void calcTotalNumberOfVertices() {
                if (isNumberOfQuadsPerVertexUniform)
                    totalNumberOfVertices = std::max<Rt::u4>(numberOfQuadsPerVertex, 1) * numberOfVertices;
                else
                    totalNumberOfVertices =
                        std::accumulate(quadsPerVertex.begin(), quadsPerVertex.end(), 0, [](I accum, I quadsPerVertex) -> I {
                            return accum + std::max<I>(quadsPerVertex, 1);
                        });
            }

            void calcDataSizes() {
                dataSize.coords = totalNumberOfVertices * sizeof(Math::Vector<float>);
                dataSize.normals = dataSize.coords;
                dataSize.colors = totalNumberOfVertices * sizeof(Color::RGBA<float>);
                dataSize.d0 = numberOfVertices * sizeof(I);
                dataSize.d1 = numberOfEdges * sizeof(Math::Geometry::Edge<I>);
                dataSize.d2 = GL::trianglesPerQuad * numberOfQuads * sizeof(Math::Geometry::Triangle<I>);
            }

            void calcDataOffsets() {
                dataOffset.coords = 0;
                dataOffset.normals = dataOffset.coords + dataSize.coords;
                dataOffset.colors = dataOffset.normals + dataSize.normals;
                dataOffset.d0 = dataOffset.colors + dataSize.colors;
                dataOffset.d1 = dataOffset.d0 + dataSize.d0;
                dataOffset.d2 = dataOffset.d1 + dataSize.d1;
            }

            I getVertexOffset(I vertex) {
                if (isNumberOfQuadsPerVertexUniform)
                    return std::max<I>(numberOfQuadsPerVertex, 1) * vertex;

                return vertexOffsets[vertex];
            }

        public:
            Data() {}

            Data(D dim, const std::shared_ptr<Math::Geometry::Topology<D, I>>& topology, const std::vector<float>& coords)
            {
                this->dim = dim;
                this->topology = topology;
                this->coords = coords;

                isNumberOfEdgesPerVertexUniform = true; // topology->isElementsCountUniform(0, 1);
                isNumberOfQuadsPerVertexUniform = true; // topology->isElementsCountUniform(0, 2);
                numberOfVertices = topology->getCount(0);
                numberOfEdges = topology->getCount(1);
                numberOfQuads = topology->getCount(2);

                initVerticesEdges();
                initVerticesQuads();
                calcVerticesOffsets();
                calcTotalNumberOfVertices();
                calcDataSizes();
                calcDataOffsets();

                dataSize.whole = dataOffset.d2 + dataSize.d2;

                data.coords.resize(totalNumberOfVertices);
                data.colors.resize(totalNumberOfVertices);
                auto coordsPtr = data.coords.data();
                auto modelVerticesPtr = coords.data();
                auto coordComponentsCount = (dim >= 3 ? 3 : dim);

                if (isNumberOfQuadsPerVertexUniform) {
                    for (I copyId = 0; copyId < std::max<I>(numberOfQuadsPerVertex, 1); copyId++)
                        Rt::stridedCopy((Rt::u1*)modelVerticesPtr, dim * sizeof(float),
                                        (Rt::u1*)(coordsPtr + copyId), std::max<I>(numberOfQuadsPerVertex, 1) * sizeof(Math::Vector<float>),
                                        coordComponentsCount * sizeof(float), numberOfVertices);
                }
                else {
                    for (I vertex = 0; vertex < numberOfVertices; vertex++)
                        for (I copyId = 0; copyId < std::max<I>(quadsPerVertex[vertex], 1); copyId++)
                            memcpy(coordsPtr + getVertexOffset(vertex) + copyId,
                                   modelVerticesPtr + dim * vertex,
                                   coordComponentsCount * sizeof(float));
                }

                data.d0.resize(numberOfVertices);
                for (I i = 0; i < numberOfVertices; i++)
                    data.d0[i] = getVertexOffset(i);

                if (dim == 1)
                    for (I i = 0; i < totalNumberOfVertices; i++)
                        coordsPtr[i].y = coordsPtr[i].z = 0.0f;

                if (dim == 2)
                    for (I i = 0; i < totalNumberOfVertices; i++)
                        coordsPtr[i].z = 0.0f;

                if (dim >= 1)
                {
                    data.d1.resize(numberOfEdges);
                    for (I i = 0; i < numberOfEdges; i++)
                    {
                        auto vertices = topology->getElements(i, 1, 0);
                        data.d1[i].a = getVertexOffset(vertices[0]);
                        data.d1[i].b = getVertexOffset(vertices[1]);
                    }

                    if (dim >= 2)
                    {
                        data.normals.resize(totalNumberOfVertices);
                        data.d2.resize(numberOfQuads * GL::trianglesPerQuad);

                        std::vector<I> counters(numberOfVertices);
                        std::fill_n(counters.begin(), numberOfVertices, 0);

                        I triangleIndex = 0;
                        for (I quad = 0; quad < numberOfQuads; quad++)
                        {
                            auto vertices = topology->getElements(quad, 2, 0);

                            I actualVertexIndices[4] = {
                                getVertexOffset(vertices[0]) + counters[vertices[0]],
                                getVertexOffset(vertices[1]) + counters[vertices[1]],
                                getVertexOffset(vertices[2]) + counters[vertices[2]],
                                getVertexOffset(vertices[3]) + counters[vertices[3]]
                            };

                            data.d2[triangleIndex].a = actualVertexIndices[0];
                            data.d2[triangleIndex].b = actualVertexIndices[1];
                            data.d2[triangleIndex].c = actualVertexIndices[2];
                            triangleIndex++;

                            data.d2[triangleIndex].a = actualVertexIndices[2];
                            data.d2[triangleIndex].b = actualVertexIndices[1];
                            data.d2[triangleIndex].c = actualVertexIndices[3];
                            triangleIndex++;

                            Math::Vector<float> v01 = data.coords[actualVertexIndices[1]] - data.coords[actualVertexIndices[0]];
                            Math::Vector<float> v02 = data.coords[actualVertexIndices[2]] - data.coords[actualVertexIndices[0]];

                            auto normal = Math::calcNormal(v01, v02);
                            //normal.x = 0.0f;
                            //normal.y = 0.0f;
                            //normal.z = 0.0f;
                            data.normals[actualVertexIndices[0]] = normal;
                            data.normals[actualVertexIndices[1]] = normal;
                            data.normals[actualVertexIndices[2]] = normal;
                            data.normals[actualVertexIndices[3]] = normal;
                            //v01.print();
                            //v02.print();
                            //normal.print();

                            for (Rt::u1 vertex = 0; vertex < 4; vertex++)
                                counters[vertices[vertex]]++;
                        }
                    }
                }

                buffer = std::make_shared<GL::Buffer>();
                auto target = GL::Buffer::Target::CopyWrite;

                buffer->bind(target);
                GL::Buffer::data(target, dataSize.whole, nullptr, GL_STATIC_DRAW);

                auto ptr = GL::Buffer::map(target, GL::Buffer::Access::Write);
                if (!ptr) Rt::error(0x843B3344);

                memcpy(((Rt::u1*)ptr) + dataOffset.coords, data.coords.data(), dataSize.coords);
                if (dim >= 1) {
                    if (dim >= 2) memcpy(((Rt::u1*)ptr) + dataOffset.normals, data.normals.data(), dataSize.normals);
                    memcpy(((Rt::u1*)ptr) + dataOffset.d0, data.d0.data(), dataSize.d0);
                    memcpy(((Rt::u1*)ptr) + dataOffset.d1, data.d1.data(), dataSize.d1);
                    if (dim >= 2) memcpy(((Rt::u1*)ptr) + dataOffset.d2, data.d2.data(), dataSize.d2);
                }

                #if 0
                printf("coords:\n");
                for (int i = 0; i < numberOfVertices * std::max<I>(1, numberOfEdgesPerVertex); i++) {
                    auto fPtr = ((float*)ptr) + i * 3;
                    printf("%f %f %f\n", fPtr[0], fPtr[1], fPtr[2]);
                }

                printf("normals:\n");
                for (int i = 0; i < numberOfVertices * std::max<I>(1, numberOfEdgesPerVertex); i++) {
                    auto fPtr = ((float*)ptr) + i * 3 + 3 * numberOfVertices * std::max<Rt::u4>(1, numberOfEdgesPerVertex);
                    printf("%f %f %f\n", fPtr[0], fPtr[1], fPtr[2]);
                }

                printf("d1:");
                for (int i = 0; i < numberOfEdges; i++) {
                    auto iptr = ((I*)((Rt::u1*)ptr + dataSize.coords + dataSize.normals + dataSize.colors)) + i * 2;
                    printf("%u %u\n", iptr[0], iptr[1]);
                }
                #endif

                GL::Buffer::unmap(target);

                setAttr("coord", buffer, GL::VertexArray::AttribPointer(3, GL_FLOAT, GL_FALSE, 0, dataOffset.coords));
                setAttr("normal", buffer, GL::VertexArray::AttribPointer(3, GL_FLOAT, GL_FALSE, 0, dataOffset.normals));
                setAttr("color", buffer, GL::VertexArray::AttribPointer(4, GL_FLOAT, GL_FALSE, 0, dataOffset.colors));

                setElements(buffer);
            }

            virtual ~Data() {}

            D getDim() const {
                return dim;
            }

            std::shared_ptr<Math::Geometry::Topology<D, I>>& getTopology() {
                return topology;
            }

            I getNumberOfVertices() const {
                return numberOfVertices;
            }

            I getNumberOfEdges() const {
                return numberOfEdges;
            }

            I getNumberOfQuads() const {
                return numberOfQuads;
            }

            Rt::u4 getCoordsOffset() const {
                return dataOffset.coords;
            }

            Rt::u4 getNormalsOffset() const {
                return dataOffset.normals;
            }

            Rt::u4 getColorsOffset() const {
                return dataOffset.colors;
            }

            Rt::u4 getPointsOffset() const {
                return dataOffset.d0;
            }

            Rt::u4 getEdgesOffset() const {
                return dataOffset.d1;
            }

            Rt::u4 getTrianglesOffset() const {
                return dataOffset.d2;
            }

            void transformCoord(const float* input, float* output, const Rotations& rotations) {
                memcpy(output, input, dim * sizeof(float));
                for (auto& rot : rotations) {
                    float x[] = { output[rot.dim[0]], output[rot.dim[1]] };
                    output[rot.dim[0]] = rot.cos * x[0] - rot.sin * x[1];
                    output[rot.dim[1]] = rot.sin * x[0] + rot.cos * x[1];
                }
    #if 0
                for (int i = 0; i < dim; i++)
                    printf("%f ", output[i]);
                printf("\n");
    #endif
            }

            void transformCoords(const Rotations& rotations)
            {
                auto output = std::unique_ptr<float[]>(new float[dim]);

                for (I vertex = 0; vertex < numberOfVertices; vertex++)
                {
                    transformCoord(coords.data() + dim * vertex, output.get(), rotations);

                    auto quadsCount = isNumberOfQuadsPerVertexUniform ? numberOfQuadsPerVertex : quadsPerVertex[vertex];
                    auto numberOfCopies = std::max<I>(quadsCount, 1);

                    for (I copyId = 0; copyId < numberOfCopies; copyId++)
                        memcpy(data.coords.data() + getVertexOffset(vertex) + copyId, output.get(), sizeof(Math::Vector<float>));
                }

    //            for (Rt::u4 quad = 1; quad < numberOfQuadsPerVertex; quad++)
    //                memcpy(data.coords.get() + numberOfVertices * quad, data.coords.get(), numberOfVertices * sizeof(Math::Vector<float>));
            }

            void calcNormals()
            {
                if (dim >= 2)
                {
                    std::vector<I> counters;
                    counters.resize(numberOfVertices);
                    std::fill_n(counters.begin(), numberOfVertices, 0);

                    I triangleIndex = 0;
                    for (I quad = 0; quad < numberOfQuads; quad++)
                    {
                        auto vertices = topology->getElements(quad, 2, 0);

                        I actualVertexIndices[4] = {
                            getVertexOffset(vertices[0]) + counters[vertices[0]],
                            getVertexOffset(vertices[1]) + counters[vertices[1]],
                            getVertexOffset(vertices[2]) + counters[vertices[2]],
                            getVertexOffset(vertices[3]) + counters[vertices[3]]
                        };

                        Math::Vector<float> v01 = data.coords[actualVertexIndices[1]] - data.coords[actualVertexIndices[0]];
                        Math::Vector<float> v02 = data.coords[actualVertexIndices[2]] - data.coords[actualVertexIndices[0]];

                        auto normal = Math::calcNormal(v01, v02);
                        data.normals[actualVertexIndices[0]] = normal;
                        data.normals[actualVertexIndices[1]] = normal;
                        data.normals[actualVertexIndices[2]] = normal;
                        data.normals[actualVertexIndices[3]] = normal;
                        //normal.print();

                        for (Rt::u1 vertex = 0; vertex < 4; vertex++)
                            counters[vertices[vertex]]++;
                    }
                }
            }

            void updateCoords() {
                buffer->bind(GL::Buffer::Target::Array);
                GL::Buffer::subData(GL::Buffer::Target::Array, dataOffset.coords, dataSize.coords, data.coords.data());
    #if 0
                for (int i = 0; i < data.coords.size(); i++) data.coords[i].print();
    #endif
            }

            void updateNormals() {
                buffer->bind(GL::Buffer::Target::Array);
                GL::Buffer::subData(GL::Buffer::Target::Array, dataOffset.normals, dataSize.normals, data.normals.data());
            }
/*
            void setColor(const Color::RGBA<float>& color) {
                vertexArray->bind();
                    auto location = program->get()->getAttributeLocation("color");
                    if (location.defined)
                        glVertexAttrib4f(location.get(), color.r, color.g, color.b, color.a);
                GL::VertexArray::unbind();
            }
*/
            void setColorsArray(const std::vector<Color::RGBA<float>>& colors)
            {
                if (isNumberOfQuadsPerVertexUniform) {
                    auto numberOfCopies = std::max<I>(numberOfQuadsPerVertex, 1);
                    for (I vertex = 0; vertex < numberOfVertices; vertex++) {
                        for (I copyId = 0; copyId < numberOfCopies; copyId++)
                            data.colors[getVertexOffset(vertex) + copyId] = colors[vertex];
                    }
                }
                else {
                    for (I vertex = 0; vertex < numberOfVertices; vertex++) {
                        auto numberOfCopies = std::max<I>(quadsPerVertex[vertex], 1);
                        for (I copyId = 0; copyId < numberOfCopies; copyId++)
                            data.colors[getVertexOffset(vertex) + copyId] = colors[vertex];
                    }
                }

                buffer->bind(GL::Buffer::Target::Array);
                GL::Buffer::subData(GL::Buffer::Target::Array, dataOffset.colors, dataSize.colors, data.colors.data());
            }

            void print() const
            {
                printf("Model:\n");
                printf("  vertices: %u\n", numberOfVertices);
                printf("  d1: %u\n", numberOfEdges);
                printf("  d2: %u\n", 2 * numberOfQuads);

                printf("  d1 per vertex: ");
                if (isNumberOfEdgesPerVertexUniform) printf("%u\n", numberOfEdgesPerVertex);
                else printf("varies\n");

                printf("  quads per vertex: ");
                if (isNumberOfQuadsPerVertexUniform) printf("%u\n", numberOfQuadsPerVertex);
                else printf("varies\n");

                printf(" coords data size: %u b\n", dataSize.coords);
                printf(" coords data size: %u b\n", dataSize.coords);
            }
        };
    }
}

#endif
