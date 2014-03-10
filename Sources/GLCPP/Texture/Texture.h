#ifndef header_E9D52C8BF536
#define header_E9D52C8BF536

namespace GL
{
    class Texture : public Object
    {
    public:
        enum class InternalFormat : GLint
        {
//            Alpha4 = GL_ALPHA4,
//            Alpha8 = GL_ALPHA8,
//            Alpha12 = GL_ALPHA12,
//            Alpha16 = GL_ALPHA16,
//            Luminance = GL_LUMINANCE,
//            Luminance4 = GL_LUMINANCE4,
//            Luminance8 = GL_LUMINANCE8,
//            Luminance12 = GL_LUMINANCE12,
//            Luminance16 = GL_LUMINANCE16,
//            LuminanceAlpha = GL_LUMINANCE_ALPHA,
//            Luminance4Alpha4 = GL_LUMINANCE4_ALPHA4,
//            Luminance6Alpha2 = GL_LUMINANCE6_ALPHA2,
//            Luminance8Alpha8 = GL_LUMINANCE8_ALPHA8,
//            Luminance12Alpha4 = GL_LUMINANCE12_ALPHA4,
//            Luminance12Alpha12 = GL_LUMINANCE12_ALPHA12,
//            Luminance16Alpha16= GL_LUMINANCE16_ALPHA16,
//            Intensity = GL_INTENSITY,
//            Intensity4 = GL_INTENSITY4,
//            Intensity8 = GL_INTENSITY8,
//            Intensity12 = GL_INTENSITY12,
//            Intensity16 = GL_INTENSITY16,
            Alpha   = GL_ALPHA,
            RGB     = GL_RGB,
            R3G3B2  = GL_R3_G3_B2,
            RGB4    = GL_RGB4,
            RGB5    = GL_RGB5,
            RGB8    = GL_RGB8,
            RGB10   = GL_RGB10,
            RGB12   = GL_RGB12,
            RGB16   = GL_RGB16,
            RGBA    = GL_RGBA,
            RGBA2   = GL_RGBA2,
            RGBA4   = GL_RGBA4,
            RGB5A1  = GL_RGB5_A1,
            RGBA8   = GL_RGBA8,
            RGB10A2 = GL_RGB10_A2,
            RGBA12  = GL_RGBA12,
            RGBA16  = GL_RGBA16
        };

    private:
        static void bind(TextureTarget target, GLuint ID);

    public:
        Texture();
        Texture(TextureTarget);
        virtual ~Texture() {}

        static void setActiveUnit(GLuint unit);
        static GLuint getActiveUnit();

        static void bind(TextureTarget target, const Texture& texture);
        static void bind(TextureTarget target, const Texture* texture);
        static void unbind(TextureTarget target);

        static void image1D(TextureTarget target, GLint level, InternalFormat internalFormat,
                            GLsizei width, GLint border,
                            PixelData::Format format, PixelData::Type type,
                            const GLvoid* data);

        static void image2D(TextureTarget target, GLint level, InternalFormat internalFormat,
                            GLsizei width, GLsizei height, GLint border,
                            PixelData::Format format, PixelData::Type type,
                            const GLvoid* data);

        static void image3D(TextureTarget target, GLint level, InternalFormat internalFormat,
                            GLsizei width, GLsizei height, GLsizei depth, GLint border,
                            PixelData::Format format, PixelData::Type type,
                            const GLvoid* data);

        static void copyImage1D(TextureTarget target, GLint level, InternalFormat internalFormat,
                                GLint x, GLint y,
                                GLsizei width, GLint border);

        static void copyImage2D(TextureTarget target, GLint level, InternalFormat internalFormat,
                                GLint x, GLint y,
                                GLsizei width, GLsizei height, GLint border);

        static void subImage1D(TextureTarget target, GLint level,
                               GLint xOffset,
                               GLsizei width,
                               PixelData::Format format, PixelData::Type type,
                               const void *data);

        static void subImage2D(TextureTarget target, GLint level,
                               GLint xOffset, GLint yOffset,
                               GLsizei width, GLsizei height,
                               PixelData::Format format, PixelData::Type type,
                               const void* data);

        static void subImage3D(TextureTarget target, GLint level,
                               GLint xOffset, GLint yOffset, GLint zOffset,
                               GLsizei width, GLsizei height, GLsizei depth,
                               PixelData::Format format, PixelData::Type type,
                               const void* data);

        static void copySubImage1D(TextureTarget target, GLint level,
                                   GLint xOffset,
                                   GLint x, GLint y,
                                   GLsizei width);

        static void copySubImage2D(TextureTarget target, GLint level,
                                   GLint xOffset, GLint yOffset,
                                   GLint x, GLint y,
                                   GLsizei width, GLsizei height);

        static void copySubImage3D(TextureTarget target, GLint level,
                                   GLint xOffset, GLint yOffset, GLint zOffset,
                                   GLint x, GLint y,
                                   GLsizei width, GLsizei height);

        static void setSamplingState(TextureTarget target, const SamplingState& state);

        static void generateMipmap(TextureTarget target);
    };
}

#endif
