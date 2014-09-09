#ifndef header_937DA278B65A
#define header_937DA278B65A

namespace SG
{
    template <typename I = Rt::u4>
    class PrimitivesStream
    {
    public:
        enum class Mode {
            Points,
            Lines,
            Triangles,
            LineStrips,
            LineLoops,
            TriangleStrips,
            TriangleFans,
            LinesWithAdjacency,
            LineStripsWithAdjacency,
            TrianglesWithAdjacency,
            TriangleStripsWithAdjacency
        };

    private:
        Mode mode;
        std::vector<I> vertices;
        Rt::Option<I> restartIndex;

    public:
        PrimitivesStream(Mode mode,
                         const std::vector<I>& vertices,
                         Rt::Option<I> restartIndex = Rt::Option<I>())
        {
            setMode(mode);
            setVertices(vertices);
            setRestartIndex(restartIndex);
        }

        Mode getMode() const {
            return mode;
        }

        void setMode(Mode mode) {
            this->mode = mode;
        }

        const std::vector<Rt::u4>& getVertices() const {
            return vertices;
        }

        std::vector<Rt::u4>& getVertices() {
            return vertices;
        }

        void setVertices(const std::vector<I>& vertices) {
            this->vertices = vertices;
        }

        Rt::Option<I> getRestartIndex() const {
            return restartIndex;
        }

        void setRestartIndex(Rt::Option<I> restartIndex) {
            this->restartIndex = restartIndex;
        }
    };
}

#endif
