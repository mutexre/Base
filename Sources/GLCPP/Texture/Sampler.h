#ifndef header_A9AAC30B5409
#define header_A9AAC30B5409

namespace GL
{
    class Sampler : public Object
    {
    private:
        static void bind(GLuint textureUnit, GLuint ID);

    public:
        Sampler();
        virtual ~Sampler() {}

        static void bind(GLuint textureUnit, const Sampler& sampler);
        static void bind(GLuint textureUnit, const Sampler* sampler);
        static void unbind(GLuint textureUnit);

        static void setSamplingState(TextureTarget target, const SamplingState& state);
    };
}

#endif
