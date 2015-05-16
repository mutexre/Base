#ifndef header_2FD4BF8F_42E3_499B_9E61_6BD6A6EC0A13
#define header_2FD4BF8F_42E3_499B_9E61_6BD6A6EC0A13

namespace Rt
{
    inline u4 mantissa(f4 a)
    {
        u4 b = *((u4*)(&a));
        return (b & 0x7FFFFF) << 9;
    }

    inline u1 exponent(f4 a)
    {
        u4 b = *((u4*)(&a));
        return ((b & 0x7F800000) >> 23) - 127;
    }

    inline s1 sign(f4 a)
    {
        u4 b = *((Rt::u4*)(&a));
        return !getBit(b, 31) ? 1 : -1;
    }
}

#endif
