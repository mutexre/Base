#ifndef header_1B37AF92C6D6
#define header_1B37AF92C6D6

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>

using boost::multi_index_container;
using boost::multi_index::indexed_by;
using boost::multi_index::ordered_unique;
using boost::multi_index::ordered_non_unique;
using boost::multi_index::member;
using boost::multi_index::tag;

namespace GL
{
    class ShaderProgram : public Object
    {
    public:
        class Sources
        {
        public:
            std::string vertex, fragment;
            Rt::Option<std::string> geometry;

        public:
            Sources() {}
            Sources(std::string vertex, std::string fragment);
            Sources(std::string vertex, std::string geometry, std::string fragment);
        };

        class LinkError : std::exception
        {
        protected:
            std::string log;

        public:
            LinkError() {}

            LinkError(std::string log) {
                this->log = log;
            }

            virtual const char* what() const throw() {
                return log.c_str();
            }
        };
/*
        struct Variable {
            virtual void set(const Rt::u1*, GLboolean transpose = GL_FALSE) const = 0;
        };
*/
        struct Attribute// : public Variable
        {
            std::string name;
            GLint index;
            GLint location;
            GLenum type;
            GLint size;

            void set(const Rt::u1*) const;
            //virtual void set(const Rt::Value::Trait* value) const;
        };

        struct Uniform// : public Variable
        {
            std::string name;
            GLint index;
            GLint location;
            GLenum type;
            GLint size;
            GLint blockIndex;
            GLint offset;
            GLint arrayStride;
            GLint matrixStride;
            GLint isRowMajor;

            GLsizeiptr calcSize() const;
            virtual void set(const Rt::u1*, GLboolean transpose = GL_FALSE) const;
            //virtual void set(const Rt::Value::Trait*, GLboolean transpose = GL_FALSE) const;
        };

        struct UniformBlock
        {
            typedef boost::bimap<GLint, std::string> ActiveUniforms;

            std::string name;
            GLint index;
            GLint dataSize;
            GLint binding;
            ActiveUniforms activeUniforms;
            struct ReferencedBy {
                GLint vertex;
                GLint fragment;
                GLint geometry;
            }
            referencedBy;
        };

        struct TFVarying {
            GLenum type;
            GLint size;
        };

        typedef std::map<GLuint, std::string> FragDataLocations;
        typedef std::set<std::string> TFVaryingNames;

    protected:
        struct Name {};
        struct Index {};
        struct Location {};
 
 #if defined _WIN32 || defined _WIN64
        typedef multi_index_container<Attribute, indexed_by<ordered_unique<tag<Name>, member<Attribute, std::string, &Attribute::name>>,
                                                            ordered_unique<tag<Index>, member<Attribute, GLint, &Attribute::index>>,
                                                            ordered_non_unique<tag<Location>, member<Attribute, GLint, &Attribute::location>>>> Attributes;
        
        typedef multi_index_container<Uniform, indexed_by<ordered_unique<tag<Name>, member<Uniform, std::string, &Uniform::name>>,
                                                          ordered_unique<tag<Index>, member<Uniform, GLint, &Uniform::index>>,
                                                          ordered_non_unique<tag<Location>, member<Uniform, GLint, &Uniform::location>>>> Uniforms;
        
        typedef multi_index_container<UniformBlock, indexed_by<ordered_unique<tag<Name>, member<UniformBlock, std::string, &UniformBlock::name>>,
                                                               ordered_unique<tag<Index>, member<UniformBlock, GLint, &UniformBlock::index>>>> UniformBlocks;
#else
        template <class T>
        using IndexedByNameIndexLocation = multi_index_container<T, indexed_by<ordered_unique<tag<Name>, member<T, std::string, &T::name>>,
                                                                               ordered_unique<tag<Index>, member<T, GLint, &T::index>>,
                                                                               ordered_non_unique<tag<Location>, member<T, GLint, &T::location>>>>;

        template <class T>
        using IndexedByNameIndex = multi_index_container<T, indexed_by<ordered_unique<tag<Name>, member<T, std::string, &T::name>>,
                                                                       ordered_unique<tag<Index>, member<T, GLint, &T::index>>>>;

        typedef IndexedByNameIndexLocation<Attribute> Attributes;
        typedef IndexedByNameIndexLocation<Uniform> Uniforms;
        typedef IndexedByNameIndex<UniformBlock> UniformBlocks;
#endif

        typedef std::map<std::string, TFVarying> TFVaryings;

    public:
        struct {
            std::shared_ptr<VertexShader> vertex;
            std::shared_ptr<GeometryShader> geometry;
            std::shared_ptr<FragmentShader> fragment;
        }
        shaders;

    protected:
        Attributes attributes;
        Uniforms uniforms;
        UniformBlocks uniformBlocks;
        TFVaryings tfVaryings;

    private:
        ShaderProgram();

    protected:
        void loadAttributes();
        void loadUniforms();
        void loadUniformBlocks();
        void loadTFVaryings();

        GLsizeiptr getUniformBlockSize(GLint) const;

        void init(std::shared_ptr<VertexShader> vertexShader,
                  Rt::Option<std::shared_ptr<GeometryShader>> geometryShader,
                  std::shared_ptr<FragmentShader> fragmentShader,
                  FragDataLocations = FragDataLocations(),
                  TFVaryingNames separate = TFVaryingNames(),
                  TFVaryingNames interleaved = TFVaryingNames());

    public:
        ShaderProgram(std::shared_ptr<VertexShader> vertexShader,
                      Rt::Option<std::shared_ptr<GeometryShader>> geometryShader,
                      std::shared_ptr<FragmentShader> fragmentShader,
                      FragDataLocations = FragDataLocations(),
                      TFVaryingNames separate = TFVaryingNames(),
                      TFVaryingNames interleaved = TFVaryingNames());

        ShaderProgram(Sources& src,
                      FragDataLocations = FragDataLocations(),
                      TFVaryingNames separate = TFVaryingNames(),
                      TFVaryingNames interleaved = TFVaryingNames());

        virtual ~ShaderProgram() {}

        //ShaderProgram(ShaderProgram&& that);

        static void bind(GLuint ID);
        static void bind(const ShaderProgram& shaderProgram);
        static void bind(const ShaderProgram* shaderProgram);
        static void unbind();

        void bind();

        static GLint getCurrentProgram();

        virtual void link();
        void loadVariables();

		GLint getInfo(GLenum parameter);

        static void enableAttribArray(GLint);
        void enableAttribArray(std::string);
        void bindFragDataLocation(GLuint index, std::string);
        void setTransformFeedbackVaryings(GLsizei count, const GLchar** varyings, GLenum bufferMode);
        void setTransformFeedbackVaryings(TFVaryingNames, GLenum bufferMode);

        void printTransformFeedbackVaryingsInfo();

        const Attributes& getAttributes() const;
        const Uniforms& getUniforms() const;
        const UniformBlocks& getUniformBlocks() const;
        const TFVaryings& getTFVaryings() const;

        Rt::Option<GLint> getAttributeLocation(std::string);

// Uniforms
        Rt::Option<Uniform> getUniform(GLuint);
        Rt::Option<Uniform> getUniform(std::string);

        Rt::Option<std::string> getUniformName(GLint);
        Rt::Option<GLint> getUniformIndex(std::string);

        Rt::Option<GLint> getUniformLocation(GLuint);
        Rt::Option<GLint> getUniformLocation(std::string);

        Rt::Option<GLenum> getUniformType(GLuint);
        Rt::Option<GLenum> getUniformType(std::string);

        Rt::Option<GLint> getUniformSize(GLuint);
        Rt::Option<GLint> getUniformSize(std::string);

        Rt::Option<GLint> getBlockIndexOfUniform(GLuint);
        Rt::Option<GLint> getBlockIndexOfUniform(std::string);

        Rt::Option<GLint> getUniformOffset(GLuint);
        Rt::Option<GLint> getUniformOffset(std::string);

        Rt::Option<GLint> getUniformArrayStride(GLuint);
        Rt::Option<GLint> getUniformArrayStride(std::string);

        Rt::Option<GLint> getUniformMatrixStride(GLuint);
        Rt::Option<GLint> getUniformMatrixStride(std::string);

        Rt::Option<GLint> isUniformRowMajor(GLuint);
        Rt::Option<GLint> isUniformRowMajor(std::string);

        void setAttribute(GLuint, const Rt::u1*);
        void setAttribute(std::string, const Rt::u1*);

        void setUniform(GLuint, const Rt::u1*);
        void setUniform(std::string, const Rt::u1*);

// Uniform blocks
        Rt::Option<UniformBlock> getUniformBlock(GLuint);
        Rt::Option<UniformBlock> getUniformBlock(std::string);

        Rt::Option<GLint> getUniformBlockName(GLuint);
        Rt::Option<GLint> getUniformBlockIndex(std::string);

        Rt::Option<GLint> getUniformBlockDataSize(GLuint);
        Rt::Option<GLint> getUniformBlockDataSize(std::string);

        Rt::Option<GLint> getUniformBlockBinding(GLuint);
        Rt::Option<GLint> getUniformBlockBinding(std::string);

        Rt::Option<UniformBlock::ActiveUniforms> getUniformBlockActiveUniforms(GLuint);
        Rt::Option<UniformBlock::ActiveUniforms> getUniformBlockActiveUniforms(std::string);

        void setUniformBlockBinding(GLuint, GLuint);
        void setUniformBlockBinding(std::string, GLuint);

        Rt::Option<UniformBlock::ReferencedBy> whichShadersReferenceUniformBlock(GLuint);
        Rt::Option<UniformBlock::ReferencedBy> whichShadersReferenceUniformBlock(std::string);
    };

    void printShaderProgram(const ShaderProgram&);
    void printShaderProgram(const ShaderProgram*);

    void printUniform(const ShaderProgram::Uniform&);
    void printUniformBlock(const ShaderProgram::UniformBlock&);
}

#endif
