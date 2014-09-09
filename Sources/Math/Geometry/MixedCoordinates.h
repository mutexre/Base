#ifndef header_7D4A81C8E38C
#define header_7D4A81C8E38C

namespace Math
{
    namespace Geometry
    {
        template <typename T = float, typename D = Rt::u1, typename I = Rt::u4>
        std::vector<T> gather(const std::vector<std::vector<T>>& sources, D srcAttrSize, I count)
        {
            auto srcAttrSizeInBytes = srcAttrSize * sizeof(T);
            auto dstAttrSize = srcAttrSize * sources.size();
            auto dstAttrSizeInBytes = dstAttrSize * sizeof(T);
            std::vector<T> dest(count * dstAttrSize);

            for (D source = 0; source < sources.size(); source++)
                Rt::stridedCopy(reinterpret_cast<const Rt::u1*>(sources[source].data()), srcAttrSizeInBytes,
                                reinterpret_cast<Rt::u1*>(dest.data()) + source * srcAttrSizeInBytes, dstAttrSizeInBytes,
                                srcAttrSizeInBytes, count);

            return dest;
        }
    }
}

#endif
