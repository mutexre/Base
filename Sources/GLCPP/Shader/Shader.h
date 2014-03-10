#ifndef header_67BE49C902D3
#define header_67BE49C902D3

namespace GL
{
    class Shader : public Object
    {
    public:
        enum class Type : GLenum {
            Vertex = GL_VERTEX_SHADER,
            Geometry = GL_GEOMETRY_SHADER,
            Fragment = GL_FRAGMENT_SHADER
        };

        class CompileError : std::exception
        {
        protected:
            std::string log;

        public:
            CompileError() {}

            CompileError(std::string log) {
                this->log = log;
            }

            virtual const char* what() const throw() {
                return log.c_str();
            }
        };

    protected:
        Shader(Type);

    public:
        Shader(Type, std::string);
        virtual ~Shader() {};
    };
}

#endif
