#ifndef header_A5C51C432F6E
#define header_A5C51C432F6E

namespace GL
{
    class PixelStore
    {
    public:
        class Parameter
        {
        public:
            enum class Pack : GLenum {
                SwapBytes   = GL_PACK_SWAP_BYTES,
                LSBFirst    = GL_PACK_LSB_FIRST,
                RowLength   = GL_PACK_ROW_LENGTH,
                ImageHeight = GL_PACK_IMAGE_HEIGHT,
                SkipPixels  = GL_PACK_SKIP_PIXELS,
                SkipRows    = GL_PACK_SKIP_ROWS,
                SkipImages  = GL_PACK_SKIP_IMAGES,
                Alignment   = GL_PACK_ALIGNMENT
            };

            enum class Unpack : GLenum {
                SwapBytes   = GL_UNPACK_SWAP_BYTES,
                LSBFirst    = GL_UNPACK_LSB_FIRST,
                RowLength   = GL_UNPACK_ROW_LENGTH,
                ImageHeight = GL_UNPACK_IMAGE_HEIGHT,
                SkipPixels  = GL_UNPACK_SKIP_PIXELS,
                SkipRows    = GL_UNPACK_SKIP_ROWS,
                SkipImages  = GL_UNPACK_SKIP_IMAGES,
                Alignment   = GL_UNPACK_ALIGNMENT
            };
        };
/*
        class State
        {
        private:
            struct
            {
                swapBytes;
                LSBFirst;
                rowLength;
                imageHeight;
                skipPixels;
                skipRows;
                skipImages;
                alignment;
            }
            pack, unpack;

        public:
            State();
        };
*/
    private:
        static void get(GLenum param, GLint& value);
        static void get(GLenum param, GLfloat& value);

        static void set(GLenum param, GLint value);
        static void set(GLenum param, GLfloat value);

    public:
        static void get(Parameter::Pack param, GLint& value);
        static void get(Parameter::Pack param, GLfloat& value);
        static void get(Parameter::Unpack param, GLint& value);
        static void get(Parameter::Unpack param, GLfloat& value);

        static void set(Parameter::Pack param, GLint value);
        static void set(Parameter::Pack param, GLfloat value);
        static void set(Parameter::Unpack param, GLint value);
        static void set(Parameter::Unpack param, GLfloat value);
    };
}

#endif
