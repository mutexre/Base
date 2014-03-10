#ifndef header_60E23821FB96
#define header_60E23821FB96

namespace GL
{
    class Viewport;
    class Shader;
    class VertexShader;
    class FragmentShader;
    class ShaderProgram;
    class Buffer;
    class VertexArray;
    class Framebuffer;
    class Renderbuffer;
    class PixelStore;
    class Query;
    class Queries;
    enum class TextureTarget;
    class PixelData;
    class Texture;
    class SamplingState;
    class Sampler;
    class Renderer;
    class ViewportRenderer;

    namespace UniformBlock { class BindingPoint; }

    static const unsigned int verticesPerEdge = 2;
    static const unsigned int verticesPerTriangle = 3;
    static const unsigned int trianglesPerQuad = 2;
    static const unsigned int componentsPerCoord = 4;

    void checkErrors();
    void printState();
}

#include <Runtime/Runtime.h>
#include <Math/Math.h>
#include <GLCPP/Platform.h>
#include <GLCPP/Rect.h>
#include <GLCPP/Viewport.h>
#include <GLCPP/Object.h>
#include <GLCPP/Shader/Shader.h>
#include <GLCPP/Shader/VertexShader.h>
#include <GLCPP/Shader/GeometryShader.h>
#include <GLCPP/Shader/FragmentShader.h>
#include <GLCPP/Shader/ShaderProgram.h>
#include <GLCPP/Buffer/Buffer.h>
#include <GLCPP/VertexArray/VertexArray.h>
#include <GLCPP/Framebuffer/Framebuffer.h>
#include <GLCPP/Renderbuffer/Renderbuffer.h>
#include <GLCPP/PixelStore/PixelStore.h>
#include <GLCPP/Query/Query.h>
#include <GLCPP/Query/Queries.h>
#include <GLCPP/Texture/TextureTarget.h>
#include <GLCPP/Texture/PixelData.h>
#include <GLCPP/Texture/Texture.h>
#include <GLCPP/Texture/SamplingState.h>
#include <GLCPP/Texture/Sampler.h>
#include <GLCPP/Renderer/Renderer.h>
#include <GLCPP/Renderer/ViewportRenderer.h>
#include <GLCPP/Auxiliary/Geometry/Quad/Data.h>
#include <GLCPP/Auxiliary/Geometry/Cube/Data.h>
#include <GLCPP/Auxiliary/Geometry/Buffer.h>
#include <GLCPP/Auxiliary/Memory/Buffer.h>
#include <GLCPP/Auxiliary/Memory/Multibuffer.h>
#include <GLCPP/Auxiliary/ProgramWithSource.h>
#include <GLCPP/Auxiliary/Subroutines.h>

namespace GL {
    GLsizeiptr getSizeOfType(GLint);
    void printInfo();
    void printCurrentBindings();
}

#endif
