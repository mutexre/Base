#ifndef header_6DE984F9
#define header_6DE984F9

#include <Runtime/Runtime.h>

namespace Color
{
    typedef Rt::u4 Space;

    class Color {};
    
    template <typename T> class HSV;
    template <typename T> class HSVA;
    template <typename T> class RGB;
    template <typename T> class RGBA;
}

#include <Color/HSV.h>
#include <Color/HSVA.h>
#include <Color/RGB.h>
#include <Color/RGBA.h>
#include <Color/Subroutines.h>

#endif
