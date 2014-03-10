#ifndef header_AFE23F22B407
#define header_AFE23F22B407

namespace SG
{
    class DataBinding
    {
    protected:
        std::shared_ptr<Data> data;
        std::shared_ptr<Program> program;
        std::shared_ptr<GL::VertexArray> vertexArray;
        std::set<std::string> disabledArrays;

    public:
        DataBinding() {
            vertexArray = std::make_shared<GL::VertexArray>();
        }

        DataBinding(std::shared_ptr<Data> data, std::shared_ptr<Program> program) : DataBinding() {
            init(data, program);
        }

        virtual ~DataBinding() {}

        void init() {
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

        void init(std::shared_ptr<Data> data,
                  std::shared_ptr<Program> program)
        {
            this->data = data;
            this->program = program;
            init();
        }

        std::shared_ptr<Data> getData() const {
            return data;
        }

        void setData(std::shared_ptr<Data> data) {
            this->data = data;
            init();
        }

        std::shared_ptr<Program> getProgam() const {
            return program;
        }

        void setProgram(std::shared_ptr<Program> program) {
            this->program = program;
            init();
        }

        void enableArray(const std::string& name, bool enable = true) {
            if (enable) {
                auto iter = disabledArrays.find(name);
                if (iter != disabledArrays.end())
                    disabledArrays.erase(iter);
            }
            else
                disabledArrays.insert(name);
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
