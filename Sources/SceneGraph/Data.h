#ifndef header_71498296FC8C
#define header_71498296FC8C

namespace SG
{
    class Data
    {
    public:
        struct ArrayState {
            std::shared_ptr<GL::Buffer> buffer;
            GL::VertexArray::AttribPointer ptr;

            ArrayState() {}

            ArrayState(std::shared_ptr<GL::Buffer> buffer, GL::VertexArray::AttribPointer ptr) {
                this->buffer = buffer;
                this->ptr = ptr;
            }
        };

        using Attributes = std::map<std::string, ArrayState>;

    protected:
        std::shared_ptr<GL::Buffer> elements;
        Attributes attributes;

    public:
        Data() {}
        virtual ~Data() {}

        std::shared_ptr<GL::Buffer> getElements() const {
            return elements;
        }

        void setElements(std::shared_ptr<GL::Buffer> buffer) {
            elements = buffer;
        }

        Attributes& getAttributes() {
            return attributes;
        }

        void setAttributes(Attributes attrs) {
            attributes = attrs;
        }

        ArrayState& getAttr(const std::string& name) {
            return attributes[name];
        }

        void setAttr(const std::string& name, std::shared_ptr<GL::Buffer> buffer, const GL::VertexArray::AttribPointer& ptr) {
            attributes[name] = ArrayState(buffer, ptr);
        }
    };
}

#endif
