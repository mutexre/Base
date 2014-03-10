#ifndef header_B87279DC0090
#define header_B87279DC0090

namespace GL
{
    enum class TextureTarget
    {
        k1D = GL_TEXTURE_1D,
        k2D = GL_TEXTURE_2D,
        k3D = GL_TEXTURE_3D,
        k1DArray = GL_TEXTURE_1D_ARRAY,
        k2DArray = GL_TEXTURE_2D_ARRAY,
        kRectangle = GL_TEXTURE_RECTANGLE,
        kBuffer = GL_TEXTURE_BUFFER,
        kCubeMap = GL_TEXTURE_CUBE_MAP,
        k2DMultisample = GL_TEXTURE_2D_MULTISAMPLE,
        k2DMultisampleArray = GL_TEXTURE_2D_MULTISAMPLE_ARRAY
    };
}

#endif
