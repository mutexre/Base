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

        using Vertices = std::vector<I>;

    private:
        Mode mode;
        Vertices vertices;
        Rt::Option<I> restartIndex;

    public:
        PrimitivesStream(Mode mode,
                         const Vertices& vertices,
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

        const Vertices& getVertices() const {
            return vertices;
        }

        Vertices& getVertices() {
            return vertices;
        }

        void setVertices(const Vertices& vertices) {
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
