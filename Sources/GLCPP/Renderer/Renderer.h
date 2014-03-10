#ifndef header_53D39CFF124A
#define header_53D39CFF124A

namespace GL
{
    class Renderer : public Rt::Object
    {
    public:
        virtual ~Renderer() {}
        virtual void render() = 0;
//        virtual void setAspectRatio(float);
    };
}

#endif
