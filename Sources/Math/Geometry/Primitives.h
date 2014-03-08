#ifndef header_D8F2601A59B7
#define header_D8F2601A59B7

namespace Math
{
    namespace Geometry
    {
        template <typename T>
        struct Triangle {
            T a, b, c;
        };

        template <typename T>
        struct Edge {
            T a, b;
        };
    }
}

#endif
