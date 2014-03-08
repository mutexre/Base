#ifndef header_FED3C86FD5C2
#define header_FED3C86FD5C2

namespace Rt
{
    template <typename PermutationIterator, typename InputRandomAccessIterator, typename OutputIterator>
    OutputIterator rearrange(PermutationIterator first, PermutationIterator last, InputRandomAccessIterator input, OutputIterator result)
    {
        if (first != last)
            for (; first != last; ++first, ++result)
                *result = *(input + *first);
        return result;
    }

    template <typename T>
    void stridedCopy(const u1* src, u4 srcStride, u1* dst, u4 dstStride, u4 count) {
        for (u4 i = 0; i < count; i++, src += srcStride, dst += dstStride)
            *((T*)dst) = *((T*)src);
    }

    void stridedCopy(const u1* src, u4 srcStride, u1* dst, u4 dstStride, u4 size, u4 count);

    std::string readFile(const char* path);
    std::string readFile(const std::string& path);

    #if defined _WIN32 || defined _WIN64
        std::string readTextResource(const char* type, int id);
    #endif
}

#endif
