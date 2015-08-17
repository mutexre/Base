#ifndef header_A88614499CF5
#define header_A88614499CF5

namespace SG
{
    template <typename I>
    class FindVertexOccurencesInPrimitivesStream : public React::Transform<FindVertexOccurencesInPrimitivesStream<I>>
    {
        using VertexOccurence = std::pair<I, I>;
        using Occurences = std::map<I, std::vector<VertexOccurence>>;

        DF_IN(React::ScalarPtr<PrimitivesStream<I>>, stream, getStream, setStream, &FindVertexOccurencesInPrimitivesStream::invalidate)
        DF_OUT(React::ScalarPtr<Occurences>, occurences, getOccurences, setOccurences, &FindVertexOccurencesInPrimitivesStream::evaluate)

    protected:
        void invalidate() {
            if (occurences.get())
                occurences->invalidate();
        }

        Occurences f(const typename PrimitivesStream<I>::Vertices& vertices, Rt::u1 primitiveSize) {
            auto numberOfPrimitives = vertices.size() / primitiveSize;
            std::map<I, std::vector<VertexOccurence>> vertexOccurences;

            for (I p = 0; p < numberOfPrimitives; p++) {
                auto primitiveOffset = primitiveSize * p;
                for (auto vertexOffset = 0; vertexOffset < primitiveOffset + primitiveSize; vertexOffset++) {
                    auto vertex = vertices[vertexOffset];
                    auto occurence = std::make_pair(p, vertexOffset);

                    auto iter = vertexOccurences.find(vertex);
                    if (iter != vertexOccurences.end())
                        (*iter).second.push_back(occurence);
                    else {
                        std::vector<I> occurences;
                        occurences.push_back(occurence);
                        vertexOccurences[vertex] = occurences;
                    }
                }
            }

            return vertexOccurences;
        }

        Occurences f2(const typename PrimitivesStream<I>::Vertices& vertices, Rt::u1 primitiveSize) {
            auto numberOfPrimitives = vertices.size() / primitiveSize;
            std::map<I, std::vector<VertexOccurence>> vertexOccurences;

            for (I p = 0; p < numberOfPrimitives; p++) {
                auto primitiveOffset = primitiveSize * p;
                for (auto vertexOffset = 0; vertexOffset < primitiveOffset + primitiveSize; vertexOffset++) {
                    auto vertex = vertices[vertexOffset];
                    auto occurence = std::make_pair(p, vertexOffset);

                    auto iter = vertexOccurences.find(vertex);
                    if (iter != vertexOccurences.end())
                        (*iter).second.push_back(occurence);
                    else {
                        std::vector<I> occurences;
                        occurences.push_back(occurence);
                        vertexOccurences[vertex] = occurences;
                    }
                }
            }

            return vertexOccurences;
        }

        void evaluate() {
            auto& stream = this->stream->value();
            switch (stream.getMode()) {
                case PrimitivesStream<I>::Mode::Points:
                    occurences->set(f(stream.getVertices(), 1));
                break;

                case PrimitivesStream<I>::Mode::Lines:
                    occurences->set(f(stream.getVertices(), 2));
                break;

                case PrimitivesStream<I>::Mode::Triangles:
                    occurences->set(f(stream.getVertices(), 3));
                break;

                case PrimitivesStream<I>::Mode::LineStrips: {
                }
                break;

                case PrimitivesStream<I>::Mode::LineLoops: {
                }
                break;

                case PrimitivesStream<I>::Mode::TriangleStrips: {
                }
                break;

                case PrimitivesStream<I>::Mode::TriangleFans: {
                }
                break;

                case PrimitivesStream<I>::Mode::LinesWithAdjacency: {
                }
                break;

                case PrimitivesStream<I>::Mode::TrianglesWithAdjacency: {
                }
                break;

                case PrimitivesStream<I>::Mode::TriangleStripsWithAdjacency: {
                }
                break;

                default: break;
            }

            this->commit(this->occurences);
        }
    };
}

#endif
