#ifndef header_7918D8637FA2
#define header_7918D8637FA2

namespace GL
{
    class SamplingState
    {
        friend class Texture;
        friend class Sampler;

    public:
        enum class Parameter : unsigned int
        {
            WrapS       = (1 << 0),
            WrapT       = (1 << 1),
            WrapR       = (1 << 2),
            MinFilter   = (1 << 3),
            MagFilter   = (1 << 4),
            BorderColor = (1 << 5),
            MinLOD      = (1 << 6),
            MaxLOD      = (1 << 7),
            LODbias     = (1 << 8),
            CompareMode = (1 << 9),
            CompareFunc = (1 << 10)
        };

        enum class Wrap : GLint
        {
            Repeat = GL_REPEAT,
            MirroredRepeat = GL_MIRRORED_REPEAT,
            ClampToEdge = GL_CLAMP_TO_EDGE,
            ClampToBorder = GL_CLAMP_TO_BORDER
        };

        class Filter
        {
        public:
            enum class Min : GLint
            {
                Nearest = GL_NEAREST,
                Linear = GL_LINEAR,
                NearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST,
                NearestMipmapLinear = GL_NEAREST_MIPMAP_LINEAR,
                LinearMipmapNearest = GL_LINEAR_MIPMAP_NEAREST,
                LinearMipmapLinear = GL_LINEAR_MIPMAP_LINEAR
            };

            enum class Mag : GLint
            {
                Nearest = GL_NEAREST,
                Linear = GL_LINEAR
            };
        };

        class Compare
        {
        public:
            enum class Mode : GLint
            {
                None = GL_NONE,
                RefToTexture = GL_COMPARE_REF_TO_TEXTURE
            };

            enum class Func : GLint
            {
                LEqual = GL_LEQUAL,
                GEqual = GL_GEQUAL,
                Less = GL_LESS,
                Greater = GL_GREATER,
                Equal = GL_EQUAL,
                NotEqual = GL_NOTEQUAL,
                Always = GL_ALWAYS,
                Never = GL_NEVER
            };
        };

    private:
        unsigned int mask;

        struct {
            Wrap s; //TEXTURE_WRAP_S
            Wrap t; //TEXTURE_WRAP_T
            Wrap r; //TEXTURE_WRAP_R
        }
        wrap;

        struct {
            Filter::Min min; //TEXTURE_MIN_FILTER
            Filter::Mag mag; //TEXTURE_MAG_FILTER
        }
        filter;

        struct {
            GLfloat r, g, b, a; //TEXTURE_BORDER_COLOR
        }
        borderColor;

        struct {
            GLfloat min; //TEXTURE_MIN_LOD
            GLfloat max; //TEXTURE_MAX_LOD
            GLfloat bias; //TEXTURE_LOD_BIAS
        }
        LOD;

        struct {
            Compare::Mode mode; //TEXTURE_COMPARE_MODE
            Compare::Func func; //TEXTURE_COMPARE_FUNC
        }
        compare;

    public:
        SamplingState();
        SamplingState(Wrap s, Wrap t, Wrap r,
                      Filter::Min min, Filter::Mag mag);
        virtual ~SamplingState() {}

        bool isParameterSet(Parameter param) const;

        void getWraps(Wrap& s, Wrap& t, Wrap& r) const;
        void setWraps(Wrap s, Wrap t, Wrap r);

        Wrap getWrapS() const;
        void setWrapS(Wrap s);

        Wrap getWrapT() const;
        void setWrapT(Wrap t);

        Wrap getWrapR() const;
        void setWrapR(Wrap r);

        void getFilters(Filter::Min& min, Filter::Mag& mag) const;
        void setFilters(Filter::Min min, Filter::Mag mag);
    };
}

#endif
