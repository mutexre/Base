#ifndef header_AFE23F22B407
#define header_AFE23F22B407

namespace SG
{
    class DataBinding
    {
    protected:
        std::shared_ptr<GL::VertexArray> vertexArray;

    public:
        DataBinding() {
            vertexArray = std::make_shared<GL::VertexArray>();
        }

        virtual ~DataBinding() {}

        void bind(const std::shared_ptr<Data>& data, const std::shared_ptr<Program>& program, const std::set<std::string>& disabledArrays) {
            vertexArray->bind();

            if (data->getElements().get())
                GL::Buffer::bind(GL::Buffer::Target::ElementArray, data->getElements().get());

            for (auto& attr : data->getAttributes()) {
                auto& name = attr.first;
                auto location = program->get()->getAttributeLocation(name);
                if (location.defined) {
                    auto& arrayState = attr.second;
                    vertexArray->set(location.get(), disabledArrays.find(name) == disabledArrays.end(), arrayState.buffer, arrayState.ptr);
                }
            }

            vertexArray->unbind();
        }

        virtual void prepare() {
            vertexArray->bind();
        }

        virtual void complete() {
            vertexArray->unbind();
        }
    };
}

#endif
