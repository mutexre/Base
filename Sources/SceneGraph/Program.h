#ifndef header_760FDB3E6940
#define header_760FDB3E6940

namespace SG
{
    class Program : public Rt::Object
    {
    public:
        class VariableNotFound : public std::exception {
            virtual const char* what() const throw() {
                return "variable not found";
            }
        };

    private:
        template <typename T> struct Stamp
        {
            React::MatrixPtr<T> source;
            Rt::u8 version;

            Stamp() {}

            Stamp(React::MatrixPtr<T> source) {
                set(source);
            }

            bool match(const React::MatrixPtr<T> source) {
                return this->source == source &&
                       this->version == source->getVersion();
            }

            void set(const React::MatrixPtr<T> source) {
                this->source = source;
                this->version = source->getVersion();
            }
        };

    private:
        std::shared_ptr<GL::ShaderProgram> program;
        std::map<std::string, Stamp<float>> stamps;

    public:
        Program(GL::ShaderProgram::Sources src,
                GL::ShaderProgram::FragDataLocations fragDataLocations = GL::ShaderProgram::FragDataLocations(),
                GL::ShaderProgram::TFVaryingNames separate = GL::ShaderProgram::TFVaryingNames(),
                GL::ShaderProgram::TFVaryingNames interleaved = GL::ShaderProgram::TFVaryingNames())
        {
            program = std::make_shared<GL::ShaderProgram>(src, fragDataLocations, separate, interleaved);
        }

        std::shared_ptr<GL::ShaderProgram> get() {
            return program;
        }

        void set(std::shared_ptr<GL::ShaderProgram> program) {
            this->program = program;
        }

        void bind() {
            program->bind();
        }

        void unbind() {
            program->unbind();
        }

        void deleteStamp(const std::string& name) {
            auto iter = stamps.find(name);
            if (iter != stamps.end())
                stamps.erase(iter);
        }

        bool setVariable(const std::string& name, const Rt::u1* data)
        {
            bool found = true;

            auto& uniforms = program->getUniforms();
            auto uniform = uniforms.find(name);
            if (uniform != uniforms.end())
                uniform->set(data, GL_TRUE);
            else {
                auto& attributes = program->getAttributes();
                auto attribute = attributes.find(name);
                if (attribute != attributes.end())
                    attribute->set(data);
                else
                    found = false;
            }

            return found;
        }

        void setVariable(const std::string& name, const React::MatrixPtr<>& value)
        {
            bool match = false;

            auto stampIter = stamps.find(name);
            if (stampIter != stamps.end()) {
                auto& stamp = stampIter->second;
                match = stamp.match(value);
            }

#if 0
//            if (!match || !value->isValid())
                printf("\"%s\", %s:\n\tmatch = %s, valid = %s\n\n", this->name.c_str(), name.c_str(), match ? "y" : "n", value->isValid() ? "y" : "n");
#endif

            if (!match || !value->isValid()) {
#if 0
                printf("%s:\n", name.c_str());
                value->get().print();
#endif

                if (setVariable(name, reinterpret_cast<Rt::u1*>(value->get().getData().data()))) {
                    if (stampIter != stamps.end())
                        (*stampIter).second.set(value);
                    else
                        stamps[name] = Stamp<float>(value);
                }
#if 0
                else
                    printf("variable not set\n");
#endif
            }
        }
    };
}

#endif
