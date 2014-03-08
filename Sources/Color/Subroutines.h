#ifndef header_AFE7F2F9
#define header_AFE7F2F9

namespace Color
{
    RGB<float> rgb2rgb(RGB<Rt::u1> rgb);
    RGB<Rt::u1> rgb2rgb(RGB<float> rgb);
    HSV<float> rgb2hsv(RGB<float> rgb);
    HSV<float> rgb2hsv(RGB<Rt::u1> rgb);
    RGB<float> hsv2rgb(HSV<float> hsv);
    RGBA<float> hsva2rgba(HSVA<float> hsva);

    RGB<float> rgb2rgb(const RGB<Rt::u1>* rgb);
    RGB<Rt::u1> rgb2rgb(const RGB<float>* rgb);
    HSV<float> rgb2hsv(const RGB<float>* rgb);
    HSV<float> rgb2hsv(const RGB<Rt::u1>* rgb);
    RGB<float> hsv2rgb(const HSV<float>* hsv);

    void generateColorCycle(HSV<float> hsv, RGB<Rt::u1>* output, Rt::u4 numberOfLeds);
    void generateColorCycle(HSVA<float> hsv, RGBA<float>* output, Rt::u4 numberOfLeds);
}

#endif
