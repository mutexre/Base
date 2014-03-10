#ifndef header_520C66D07E21
#define header_520C66D07E21

namespace GL
{
    namespace AUX
    {
        struct ProgramWithSource
        {
        public:
            ShaderProgram::Sources src;
            ShaderProgram::FragDataLocations fragDataLocations;
            struct {
                ShaderProgram::TFVaryingNames separate;
                ShaderProgram::TFVaryingNames interleaved;
            }
            tfVaryings;
            std::shared_ptr<ShaderProgram> program;

        public:
            ProgramWithSource() {}

            ProgramWithSource(std::string vertex, std::string fragment, std::string geometry,
                              ShaderProgram::FragDataLocations = ShaderProgram::FragDataLocations(),
                              ShaderProgram::TFVaryingNames separate = ShaderProgram::TFVaryingNames(),
                              ShaderProgram::TFVaryingNames interleaved = ShaderProgram::TFVaryingNames())
            {
                src.vertex = vertex;
                src.fragment = fragment;
                src.geometry = geometry;
                this->fragDataLocations = fragDataLocations;
                tfVaryings.separate = separate;
                tfVaryings.interleaved = interleaved;
            }

            void init() {
                program = std::make_shared<ShaderProgram>(src, fragDataLocations, tfVaryings.separate, tfVaryings.interleaved);
            }
        };
    }
}

#endif
