#include <GLCPP/GL.h>

GL::ViewportRenderer::ViewportRenderer(Viewport viewport) {
    set(viewport);
}

void GL::ViewportRenderer::render() {
    install();
}
