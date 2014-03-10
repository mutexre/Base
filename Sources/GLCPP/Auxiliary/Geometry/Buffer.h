#ifndef header_CA65DB24835A
#define header_CA65DB24835A

namespace GL
{
    namespace AUX
    {
        namespace Geometry
        {
            template <typename Data>
            class Buffer : public GL::Buffer
            {
            public:
                static void copyData(GL::Buffer::Target, GLintptr offset);

            public:
                Buffer();
                virtual ~Buffer() {}
            };

            #include <GLCPP/Auxiliary/Geometry/BufferDefinition.h>
        }
    }
}

#endif
