#include <GLCPP/GL.h>

void GL::Sampler::bind(GLuint textureUnit, GLuint ID) {
    glBindSampler(textureUnit, ID);
}

GL::Sampler::Sampler() {
    type = Object::Type::Sampler;
    glGenSamplers(1, &ID);
    needToDelete = true;
}

void GL::Sampler::bind(GLuint textureUnit, const Sampler& sampler) {
    bind(textureUnit, sampler.getID());
}

void GL::Sampler::bind(GLuint textureUnit, const Sampler* sampler) {
    bind(textureUnit, sampler->getID());
}

void GL::Sampler::unbind(GLuint textureUnit) {
    bind(textureUnit, GLuint(0));
}

void GL::Sampler::setSamplingState(TextureTarget target, const SamplingState& state) {
    if (state.isParameterSet(SamplingState::Parameter::WrapS))
        glSamplerParameteri(GLenum(target), GL_TEXTURE_WRAP_S, GLint(state.wrap.s));

    if (state.isParameterSet(SamplingState::Parameter::WrapT))
        glSamplerParameteri(GLenum(target), GL_TEXTURE_WRAP_T, GLint(state.wrap.t));

    if (state.isParameterSet(SamplingState::Parameter::WrapR))
        glSamplerParameteri(GLenum(target), GL_TEXTURE_WRAP_R, GLint(state.wrap.r));

    if (state.isParameterSet(SamplingState::Parameter::MinFilter))
        glSamplerParameteri(GLenum(target), GL_TEXTURE_MIN_FILTER, GLint(state.filter.min));

    if (state.isParameterSet(SamplingState::Parameter::MagFilter))
        glSamplerParameteri(GLenum(target), GL_TEXTURE_MAG_FILTER, GLint(state.filter.mag));

    if (state.isParameterSet(SamplingState::Parameter::BorderColor))
        glSamplerParameterfv(GLenum(target), GL_TEXTURE_BORDER_COLOR, &(state.borderColor.r));

    if (state.isParameterSet(SamplingState::Parameter::MinLOD))
        glSamplerParameterf(GLenum(target), GL_TEXTURE_MIN_LOD, state.LOD.min);

    if (state.isParameterSet(SamplingState::Parameter::MaxLOD))
        glSamplerParameterf(GLenum(target), GL_TEXTURE_MAX_LOD, state.LOD.max);

    if (state.isParameterSet(SamplingState::Parameter::LODbias))
        glSamplerParameterf(GLenum(target), GL_TEXTURE_LOD_BIAS, state.LOD.bias);

    if (state.isParameterSet(SamplingState::Parameter::CompareMode))
        glSamplerParameteri(GLenum(target), GL_TEXTURE_COMPARE_MODE, GLint(state.compare.mode));

    if (state.isParameterSet(SamplingState::Parameter::CompareFunc))
        glSamplerParameteri(GLenum(target), GL_TEXTURE_COMPARE_FUNC, GLint(state.compare.func));
}
