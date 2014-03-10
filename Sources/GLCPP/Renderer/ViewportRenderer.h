#ifndef header_94C9742A71FF
#define header_94C9742A71FF

namespace GL
{
    class ViewportRenderer : public Renderer, public Viewport
    {
    public:
        ViewportRenderer();
        ViewportRenderer(Viewport);
        virtual ~ViewportRenderer() {}

        virtual void render() override;
    };
}

#endif
