#ifndef header_82316C573200
#define header_82316C573200

namespace SG
{
    namespace Topological
    {
        template <typename D = Rt::u1, typename I = Rt::u4>
        class Object : public SG::Object
        {
        public:
            struct Parameters {
                std::shared_ptr<SG::Program> program;
                std::shared_ptr<SG::Material> material;
                bool enableColorArray, enableDepthTest;
                Color::RGBA<float> color;
            };

        protected:
            std::shared_ptr<Data<D, I>> data;

        public:
            Object() {}

            Object(D dim,
                   const std::shared_ptr<Math::Geometry::Topology<D, I>>& topology,
                   const std::vector<float>& coords,
                   Rt::Option<Parameters> points,
                   Rt::Option<Parameters> edges,
                   Rt::Option<Parameters> faces)
            {
                init(dim, topology, coords, points, edges, faces);
            }

            virtual ~Object() {}

            void init(D dim,
                      const std::shared_ptr<Math::Geometry::Topology<D, I>>& topology,
                      const std::vector<float>& coords,
                      Rt::Option<Parameters> points,
                      Rt::Option<Parameters> edges,
                      Rt::Option<Parameters> faces)
            {
                std::shared_ptr<SG::DataBinding> dataBinding;
                std::shared_ptr<SG::DrawCall> drawCall;
                std::shared_ptr<SG::Segment> segment;

                data = std::make_shared<Data<D, I>>(dim, topology, coords);

                if (points.defined) {
                    dataBinding = std::make_shared<SG::DataBinding>(data, points.get().program);
                    drawCall = std::make_shared<SG::DrawCall>(GL_POINTS,
                                                              data->getNumberOfVertices(),
                                                              GL_UNSIGNED_INT,
                                                              data->getPointsOffset());

                    segment = std::make_shared<SG::Segment>(dataBinding, drawCall, points.get().program, points.get().material, points.get().enableDepthTest);
                    add(segment);
                }

                if (edges.defined) {
                    dataBinding = std::make_shared<SG::DataBinding>(data, edges.get().program);
                    drawCall = std::make_shared<SG::DrawCall>(GL_LINES,
                                                              GL::verticesPerEdge * data->getNumberOfEdges(),
                                                              GL_UNSIGNED_INT,
                                                              data->getEdgesOffset());

                    segment = std::make_shared<SG::Segment>(dataBinding, drawCall, edges.get().program, edges.get().material, edges.get().enableDepthTest);
                    add(segment);
                }

                if (faces.defined) {
                    dataBinding = std::make_shared<SG::DataBinding>(data, faces.get().program);
                    drawCall = std::make_shared<SG::DrawCall>(GL_TRIANGLES,
                                                              GL::trianglesPerQuad * GL::verticesPerTriangle * data->getNumberOfQuads(),
                                                              GL_UNSIGNED_INT,
                                                              data->getTrianglesOffset());

                    segment = std::make_shared<SG::Segment>(dataBinding, drawCall, faces.get().program, faces.get().material, faces.get().enableDepthTest);
                    add(segment);
                }

                //glVertexAttrib4f(attrib.location.get(), 1.0f, 1.0f, 1.0f, 0.99f);
            }

            std::shared_ptr<Data<D, I>> getData() const {
                return data;
            }
        };
    }
}

#endif
