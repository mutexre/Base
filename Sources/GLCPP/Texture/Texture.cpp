#include <GLCPP/GL.h>

void GL::Texture::bind(TextureTarget target, GLuint ID) {
    glBindTexture(GLenum(target), ID);
}

GL::Texture::Texture() {
    type = Object::Type::Texture;
    glGenTextures(1, &ID);
    needToDelete = true;
}

GL::Texture::Texture(TextureTarget target) : Texture() {
    bind(target, ID);
}

void GL::Texture::setActiveUnit(GLuint unit) {
    glActiveTexture(GL_TEXTURE0 + unit);
}

GLuint GL::Texture::getActiveUnit() {
    GLint retval;
    glGetIntegerv(GL_ACTIVE_TEXTURE, &retval);
    return retval - GL_TEXTURE0;
}

void GL::Texture::bind(TextureTarget target, const Texture& texture) {
    bind(target, texture.getID());
}

void GL::Texture::bind(TextureTarget target, const Texture* texture) {
    bind(target, texture->getID());
}

void GL::Texture::unbind(TextureTarget target) {
    bind(target, GLuint(0));
}

void GL::Texture::image1D(TextureTarget target, GLint level, InternalFormat internalFormat,
                          GLsizei width, GLint border,
                          PixelData::Format format, PixelData::Type type,
                          const GLvoid* data)
{
    glTexImage1D(GLenum(target), level, GLint(internalFormat),
                 width, border,
                 GLenum(format), GLenum(type),
                 data);
}

void GL::Texture::image2D(TextureTarget target, GLint level, InternalFormat internalFormat,
                          GLsizei width, GLsizei height, GLint border,
                          PixelData::Format format, PixelData::Type type,
                          const GLvoid* data)
{
    glTexImage2D(GLenum(target), level, GLint(internalFormat),
                 width, height, border,
                 GLenum(format), GLenum(type),
                 data);
}

void GL::Texture::image3D(TextureTarget target, GLint level, InternalFormat internalFormat,
                          GLsizei width, GLsizei height, GLsizei depth, GLint border,
                          PixelData::Format format, PixelData::Type type,
                          const GLvoid* data)
{
    glTexImage3D(GLenum(target), level, GLint(internalFormat),
                 width, height, depth, border,
                 GLenum(format), GLenum(type),
                 data);
}

void GL::Texture::copyImage1D(TextureTarget target, GLint level, InternalFormat internalFormat,
                              GLint x, GLint y,
                              GLsizei width, GLint border)
{
    glCopyTexImage1D(GLenum(target), level, GLint(internalFormat),
                     x, y,
                     width, border);
}

void GL::Texture::copyImage2D(TextureTarget target, GLint level, InternalFormat internalFormat,
                              GLint x, GLint y,
                              GLsizei width, GLsizei height, GLint border)
{
    glCopyTexImage2D(GLenum(target), level, GLint(internalFormat),
                     x, y,
                     width, height, border);
}

void GL::Texture::subImage1D(TextureTarget target, GLint level,
                             GLint xOffset,
                             GLsizei width,
                             PixelData::Format format, PixelData::Type type,
                             const void* data)
{
    glTexSubImage1D(GLenum(target), level,
                    xOffset,
                    width,
                    GLenum(format), GLenum(type),
                    data);
}

void GL::Texture::subImage2D(TextureTarget target, GLint level,
                             GLint xOffset, GLint yOffset,
                             GLsizei width, GLsizei height,
                             PixelData::Format format, PixelData::Type type,
                             const void* data)
{
    glTexSubImage2D(GLenum(target), level,
                    xOffset, yOffset,
                    width, height,
                    GLenum(format), GLenum(type),
                    data);
}

void GL::Texture::subImage3D(TextureTarget target, GLint level,
                             GLint xOffset, GLint yOffset, GLint zOffset,
                             GLsizei width, GLsizei height, GLsizei depth,
                             PixelData::Format format, PixelData::Type type,
                             const void* data)
{
    glTexSubImage3D(GLenum(target), level,
                    xOffset, yOffset, zOffset,
                    width, height, depth,
                    GLenum(format), GLenum(type),
                    data);
}

void GL::Texture::copySubImage1D(TextureTarget target, GLint level,
                                 GLint xOffset,
                                 GLint x, GLint y,
                                 GLsizei width)
{
    glCopyTexSubImage1D(GLenum(target), level,
                        xOffset,
                        x, y,
                        width);
}

void GL::Texture::copySubImage2D(TextureTarget target, GLint level,
                                 GLint xOffset, GLint yOffset,
                                 GLint x, GLint y,
                                 GLsizei width, GLsizei height)
{
    glCopyTexSubImage2D(GLenum(target), level,
                        xOffset, yOffset,
                        x, y,
                        width, height);
}

void GL::Texture::copySubImage3D(TextureTarget target, GLint level,
                                 GLint xOffset, GLint yOffset, GLint zOffset,
                                 GLint x, GLint y,
                                 GLsizei width, GLsizei height)
{
    glCopyTexSubImage3D(GLenum(target), level,
                        xOffset, yOffset, zOffset,
                        x, y,
                        width, height);
}

void GL::Texture::setSamplingState(TextureTarget target, const SamplingState& state) {
    if (state.isParameterSet(SamplingState::Parameter::WrapS))
        glTexParameteri(GLenum(target), GL_TEXTURE_WRAP_S, GLint(state.wrap.s));

    if (state.isParameterSet(SamplingState::Parameter::WrapT))
        glTexParameteri(GLenum(target), GL_TEXTURE_WRAP_T, GLint(state.wrap.t));

    if (state.isParameterSet(SamplingState::Parameter::WrapR))
        glTexParameteri(GLenum(target), GL_TEXTURE_WRAP_R, GLint(state.wrap.r));

    if (state.isParameterSet(SamplingState::Parameter::MinFilter))
        glTexParameteri(GLenum(target), GL_TEXTURE_MIN_FILTER, GLint(state.filter.min));

    if (state.isParameterSet(SamplingState::Parameter::MagFilter))
        glTexParameteri(GLenum(target), GL_TEXTURE_MAG_FILTER, GLint(state.filter.mag));

    if (state.isParameterSet(SamplingState::Parameter::BorderColor))
        glTexParameterfv(GLenum(target), GL_TEXTURE_BORDER_COLOR, &(state.borderColor.r));

    if (state.isParameterSet(SamplingState::Parameter::MinLOD))
        glTexParameterf(GLenum(target), GL_TEXTURE_MIN_LOD, state.LOD.min);

    if (state.isParameterSet(SamplingState::Parameter::MaxLOD))
        glTexParameterf(GLenum(target), GL_TEXTURE_MAX_LOD, state.LOD.max);

    if (state.isParameterSet(SamplingState::Parameter::LODbias))
        glTexParameterf(GLenum(target), GL_TEXTURE_LOD_BIAS, state.LOD.bias);

    if (state.isParameterSet(SamplingState::Parameter::CompareMode))
        glTexParameteri(GLenum(target), GL_TEXTURE_COMPARE_MODE, GLint(state.compare.mode));

    if (state.isParameterSet(SamplingState::Parameter::CompareFunc))
        glTexParameteri(GLenum(target), GL_TEXTURE_COMPARE_FUNC, GLint(state.compare.func));
}

void GL::Texture::generateMipmap(TextureTarget target) {
    glGenerateMipmap(GLenum(target));
}
