#include <algorithm>
#include <functional>
#include <Color/Color.h>

Color::RGB<float>
Color::rgb2rgb(RGB<Rt::u1> rgb) {
    return rgb2rgb(&rgb);
}

Color::RGB<Rt::u1>
Color::rgb2rgb(RGB<float> rgb) {
    return rgb2rgb(&rgb);
}

Color::HSV<float>
Color::rgb2hsv(RGB<float> rgb) {
    return rgb2hsv(&rgb);
}

Color::HSV<float>
Color::rgb2hsv(RGB<Rt::u1> rgb) {
    return rgb2hsv(&rgb);
}

Color::RGB<float>
Color::hsv2rgb(HSV<float> hsv) {
    return hsv2rgb(&hsv);
}

Color::RGBA<float>
Color::hsva2rgba(HSVA<float> that) {
    
    return hsv2rgb(&that);
}

Color::RGB<float>
Color::rgb2rgb(const RGB<Rt::u1>* rgb)
{
    return RGB<float>(float(rgb->r) / 255.0f,
                      float(rgb->g) / 255.0f,
                      float(rgb->b) / 255.0f);
}

Color::RGB<Rt::u1>
Color::rgb2rgb(const RGB<float>* rgb)
{
    return RGB<Rt::u1>(Rt::u1(rgb->r * 255.0f) & 0xff,
                       Rt::u1(rgb->g * 255.0f) & 0xff,
                       Rt::u1(rgb->b * 255.0f) & 0xff);
}

Color::HSV<float>
Color::rgb2hsv(const RGB<float>* rgb)
{
    HSV<float> hsv;
    float Max, Min;
    const float one_sixth = 1.0f / 6.0f;

    Max = std::max(rgb->r, std::max(rgb->g, rgb->b));
    Min = std::min(rgb->r, std::min(rgb->g, rgb->b));

    if (Max == Min) {
        hsv.h = 0.0f;
    }
    else {
        if (rgb->r == Max) {
            if (rgb->g >= rgb->b)
                hsv.h = one_sixth * ((rgb->g - rgb->b) / (Max - Min));
            else
                hsv.h = one_sixth * ((rgb->g - rgb->b) / (Max - Min)) + 1.0f;
        }
        else {
            if (rgb->g == Max)
                hsv.h = one_sixth * ((rgb->b - rgb->r) / (Max - Min)) + (1.0f / 3.0f);
            else
                hsv.h = one_sixth * ((rgb->r - rgb->g) / (Max - Min)) + (2.0f / 3.0f);
        }
    }

    if (Max == 0.0f) hsv.s = 0.0f;
    else hsv.s = (1.0f - (Min / Max));

    hsv.v = Max;

    return hsv;
}

Color::HSV<float>
Color::rgb2hsv(const RGB<Rt::u1>* rgb) {
    return rgb2hsv(rgb2rgb(rgb));
}

Color::RGB<float>
Color::hsv2rgb(const HSV<float>* hsv)
{
    RGB<float> rgb;
    float h_mul_6_factionalPart, p, q, t;
    auto h_mul_6 = 6.0f * hsv->h;
    float h_mul_6_integerPart;

    h_mul_6_factionalPart = modff(h_mul_6, &h_mul_6_integerPart);
    p = hsv->v * (1.0 - hsv->s);
    q = hsv->v * (1.0 - h_mul_6_factionalPart * hsv->s);
    t = hsv->v * (1.0 - (1.0 - h_mul_6_factionalPart) * hsv->s);

    switch (Rt::u1(h_mul_6_integerPart)) {
        case 0: {
            rgb.r = hsv->v;
            rgb.g = t;
            rgb.b = p;
        }
        break;

        case 1: {
            rgb.r = q;
            rgb.g = hsv->v;
            rgb.b = p;
        }
        break;

        case 2: {
            rgb.r = p;
            rgb.g = hsv->v;
            rgb.b = t;
        }
        break;

        case 3: {
            rgb.r = p;
            rgb.g = q;
            rgb.b = hsv->v;
        }
        break;

        case 4: {
            rgb.r = t;
            rgb.g = p;
            rgb.b = hsv->v;
        }
        break;

        case 5: {
            rgb.r = hsv->v;
            rgb.g = p;
            rgb.b = q;
        }
        break;
    }

    return rgb;
}

void Color::generateColorCycle(HSV<float> hsv, RGB<Rt::u1>* output, Rt::u4 n)
{
    for (int i = 0; i < n; i++) {
        float h = hsv.h + float(i) * (360.0f / float(n));
        if (h >= 360.0f) h -= 360.0f;

        HSV<float> _hsv(h, hsv.s, hsv.v);
        RGB<float> rgb = hsv2rgb(_hsv);

        output[i].set(255 * rgb.r, 255 * rgb.g, 255 * rgb.b);
    }
}

void Color::generateColorCycle(HSVA<float> hsv, RGBA<float>* output, Rt::u4 n)
{
    for (int i = 0; i < n; i++) {
        float h = hsv.h + float(i) * (360.0f / float(n));
        if (h >= 360.0f) h -= 360.0f;

        output[i] = RGBA<float>(hsv2rgb(HSVA<float>(h, hsv.s, hsv.v)), hsv.a);
    }
}
