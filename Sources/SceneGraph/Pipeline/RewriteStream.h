#ifndef header_EFB1C5B8049A
#define header_EFB1C5B8049A

namespace SG
{
    template <typename I>
    class RewriteStream : public React::Transform<RewriteStream<I>>
    {
        DF_IN(React::ScalarPtr<PrimitivesStream<I>>, inputStream, getInputStream, setInputStream, &RewriteStream::invalidate)
        DF_IN(React::ScalarPtr<typename FindVertexOccurencesInPrimitivesStream<I>::Occurences>, occurences, getOccurences, setOccurences, &RewriteStream::invalidate)
        DF_OUT(React::ScalarPtr<PrimitivesStream<I>>, outputStream, getOutputStream, setOutputStream, &RewriteStream::evaluate)

    protected:
        void invalidate() {
            if (outputStream.get())
                outputStream->invalidate();
        }

        void evaluate() {
            const auto& inputStream = this->inputStream->value();
            auto& outputStream = this->outputStream->value();
            auto& vertices = outputStream.getVertices();
            const auto& occurences = this->occurences->value();

            switch (inputStream.getMode()) {
                case PrimitivesStream<I>::Mode::Points:
                    outputStream->set(inputStream);
                break;

                case PrimitivesStream<I>::Mode::Lines:
                case PrimitivesStream<I>::Mode::Triangles: {
                    outputStream.setMode(inputStream.getMode());
                    vertices.resize(inputStream.getVertices().size());

                    I i = 0;
                    for (auto x : occurences) {
                        auto vertex = x.first;
                        const auto& occurences = x.second;

                        for (auto o : occurences) {
                            auto vertexOffset = o.second;
                            vertices[vertexOffset] = i;
                            i++;
                        }
                    }
                }
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

            this->commit(this->outputStream);
        }
    };
}

#endif
