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
                React::ScalarPtr<std::shared_ptr<SG::Program>> program;
                React::ScalarPtr<std::shared_ptr<SG::Material>> material;
                React::ScalarPtr<bool> enableColorArray;
                React::ScalarPtr<bool> enableDepthTest;
                React::ScalarPtr<Color::RGBA<float>> color;
            };

        protected:
            React::ScalarPtr<std::shared_ptr<Data<D, I>>> data;

        public:
            Object() {}

            Object(D dim,
                   const std::shared_ptr<Math::Geometry::Topology<D, I>>& topology,
                   const std::vector<float>& coords,
                   Rt::Option<Parameters> d0,
                   Rt::Option<Parameters> d1,
                   Rt::Option<Parameters> d2)
            {
                init(dim, topology, coords, d0, d1, d2);
            }

            virtual ~Object() {}

            void init(D dim,
                      const std::shared_ptr<Math::Geometry::Topology<D, I>>& topology,
                      const std::vector<float>& coords,
                      Rt::Option<Parameters> d0,
                      Rt::Option<Parameters> d1,
                      Rt::Option<Parameters> d2)
            {
                data = React::makeScalarPtr(std::make_shared<Data<D, I>>(dim, topology, coords));

                if (d0.defined) {
                    auto dataBinding = std::make_shared<SG::DataBinding>();//data, d0.get().program);
                    auto drawCall = std::make_shared<SG::DrawCall>();/*GL_POINTS,
                                                                   data->getNumberOfVertices(),
                                                                   GL_UNSIGNED_INT,
                                                                   data->getPointsOffset());*/

                    auto segment = std::make_shared<SG::Segment>(dataBinding, drawCall, d0.get().program, d0.get().material, d0.get().enableDepthTest);
                    add(segment);
                }

                if (d1.defined) {
                    auto dataBinding = std::make_shared<SG::DataBinding>();//data, d1.get().program);
                    auto drawCall = std::make_shared<SG::DrawCall>();/*GL_LINES,
                                                                   GL::verticesPerEdge * data->getNumberOfEdges(),
                                                                   GL_UNSIGNED_INT,
                                                                   data->getEdgesOffset());*/

                    auto segment = std::make_shared<SG::Segment>(dataBinding, drawCall, d1.get().program, d1.get().material, d1.get().enableDepthTest);
                    add(segment);
                }

                if (d2.defined) {
                    auto dataBinding = std::make_shared<SG::DataBinding>();//data, d2.get().program);
                    auto drawCall = std::make_shared<SG::DrawCall>();/*GL_TRIANGLES,
                                                                   GL::trianglesPerQuad * GL::verticesPerTriangle * data->getNumberOfQuads(),
                                                                   GL_UNSIGNED_INT,
                                                                   data->getTrianglesOffset());*/

                    auto segment = std::make_shared<SG::Segment>(dataBinding, drawCall, d2.get().program, d2.get().material, d2.get().enableDepthTest);
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
