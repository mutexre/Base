#ifndef header_56D3406A1A74
#define header_56D3406A1A74

namespace SG
{
    class Material
    {
    private:
        std::map<std::string, React::MatrixPtr<>> properties;

    public:
        React::MatrixPtr<> get(const std::string& name) {
            return properties[name];
        }

        void set(const std::string& name, React::MatrixPtr<> value) {
            properties[name] = value;
        }

        void applyTo(std::shared_ptr<Program> program) {
            program->bind();
            for (auto& prop : properties)
                program->setVariable(prop.first, prop.second);
        }
    };
}

#endif
