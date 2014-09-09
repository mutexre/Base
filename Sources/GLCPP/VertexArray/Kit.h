#ifndef header_5D060615232E
#define header_5D060615232E

namespace GL
{
    class VertexArrayKit : public Renderer
    {
    public:
        class Options
        {
        public:
            typedef std::set<std::shared_ptr<GL::UniformBlock::BindingPoint>> BindingPoints;

        public:
            bool enabled;
            unsigned int offset, count;
            GLenum type;
            GLint baseVertex;
            GLsizei numberOfInstances;
            std::shared_ptr<ShaderProgram> program;
            std::shared_ptr<VertexArray> array;
            std::set<std::shared_ptr<GL::UniformBlock::BindingPoint>> bindingPoints;

		protected:
            void init(bool enabled, unsigned int offset = 0, unsigned int count = 0, GLenum type = GL_UNSIGNED_INT,
                      GLint baseVertex = 0, GLsizei numberOfInstances = 0,
                      Rt::Option<std::shared_ptr<ShaderProgram>> = Rt::Option<std::shared_ptr<ShaderProgram>>(),
                      Rt::Option<std::shared_ptr<VertexArray>> = Rt::Option<std::shared_ptr<VertexArray>>(),
                      Rt::Option<std::set<std::shared_ptr<GL::UniformBlock::BindingPoint>>> = Rt::Option<std::set<std::shared_ptr<GL::UniformBlock::BindingPoint>>>());

        public:
            Options() {}

            Options(bool enabled, unsigned int offset = 0, unsigned int count = 0, GLenum type = GL_UNSIGNED_INT,
                    GLint baseVertex = 0, GLsizei numberOfInstances = 0,
                    Rt::Option<std::shared_ptr<ShaderProgram>> = Rt::Option<std::shared_ptr<ShaderProgram>>(),
                    Rt::Option<std::shared_ptr<VertexArray>> = Rt::Option<std::shared_ptr<VertexArray>>(),
                    Rt::Option<std::set<std::shared_ptr<GL::UniformBlock::BindingPoint>>> = Rt::Option<std::set<std::shared_ptr<GL::UniformBlock::BindingPoint>>>());

            Options(bool enabled, unsigned int offset, unsigned int count, GLenum type,
                    GLint baseVertex, GLsizei numberOfInstances,
                    std::shared_ptr<ShaderProgram> program,
                    Rt::Option<std::shared_ptr<VertexArray>> array = Rt::Option<std::shared_ptr<VertexArray>>(),
                    Rt::Option<std::set<std::shared_ptr<GL::UniformBlock::BindingPoint>>> = Rt::Option<std::set<std::shared_ptr<GL::UniformBlock::BindingPoint>>>());

            Options(bool enabled, unsigned int offset, unsigned int count, GLenum type,
                    GLint baseVertex, GLsizei numberOfInstances,
                    std::shared_ptr<ShaderProgram>,
                    std::shared_ptr<VertexArray>,
                    Rt::Option<std::set<std::shared_ptr<GL::UniformBlock::BindingPoint>>> = Rt::Option<std::set<std::shared_ptr<GL::UniformBlock::BindingPoint>>>());

            Options(bool enabled, unsigned int offset, unsigned int count, GLenum type,
                    GLint baseVertex, GLsizei numberOfInstances,
                    std::shared_ptr<ShaderProgram>,
                    std::shared_ptr<VertexArray>,
                    std::set<std::shared_ptr<GL::UniformBlock::BindingPoint>>);

            virtual ~Options() {}

            virtual void bind();
        };

    public:
        Options d0, d1, d2;

    public:
        VertexArrayKit();
        VertexArrayKit(Options d0,
                       Options d1,
                       Options d2);

        virtual ~VertexArrayKit() {}

        virtual void render() override;

        virtual Options getPointsOptions() const;
        virtual void setPointsOptions(Options options);
        virtual void setPointsShaderProgram(std::shared_ptr<ShaderProgram> program);

        virtual Options getLinesOptions() const;
        virtual void setLinesOptions(Options options);
        virtual void setLinesShaderProgram(std::shared_ptr<ShaderProgram> program);

        virtual Options getTrianglesOptions() const;
        virtual void setTrianglesOptions(Options options);
        virtual void setTrianglesShaderProgram(std::shared_ptr<ShaderProgram> program);

        virtual void setEnabled(bool d0, bool d1, bool d2);
    };
}

#endif
