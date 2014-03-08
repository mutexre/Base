#ifndef header_F50C1A74E87D
#define header_F50C1A74E87D

/*
0D: xxx
1D: -xx  x-x  xx-
2D: --x  -x-  x--
3D: ---

0D:
    abc:
        0D: abc
        1D: ab- a-c -bc
        2D: a-- -b- --c
        3D: ---

1D:
    ab-:
        0D: ab~
        1D: ab-
        2D: a-- -b-
        3D: ---

    a-c:
        0D: a~c
        1D: a-c
        2D: a-- --c
        3D: ---

    -bc:
        0D: ~bc
        1D: -bc
        2D: -b- --c
        3D: ---


a--:
    1D: ab- -bc a-c
*/

namespace Math
{
    namespace Geometry
    {
        namespace Internal
        {
            namespace Hypercube
            {
                template<typename D, typename I>
                class Topology
                {
                public:
                    struct Id
                    {
                        D dim;
                        I mask, value;

                        Id(D dim, I mask, I value);

                        bool operator<(const Id&) const;
                        bool operator>(const Id&) const;
    //                    bool operator<=(const Id&);
    //                    bool operator>=(const Id&);
                    };

                public:
                    static I getCount(D boundingDim, D dim);
                    static I getCount(D boundingDim, D dim, D elementsDim);
                    static I getCount(D boundingDim, Id id, D elementsDim);

                    static std::vector<Id> getElements(D boundingDim, D dim);
                    static std::vector<Id> getElements(D boundingDim, Id id, D elementsDim);

    //                I pack(D boundingDim, Id<D, I> id);
    //                Id<D, I> unpack(D boundingDim, I);
                };

                #include <Math/Internal/Geometry/Hypercube/TopologyDefinition.h>
            }
        }
    }
}

#endif
