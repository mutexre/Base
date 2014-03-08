#ifndef header_AB14AE7DA56B
#define header_AB14AE7DA56B

namespace Rt
{
    class Test
    {
    public:
        virtual ~Test() {};

        virtual int test() = 0;
        virtual int run();
    };
}

#define RTTestLog(format, ...) { RtLog("%s: " format, __func__, ##__VA_ARGS__); }
#define RTTestError(format, ...) { RtLog("%s(line %d): " format, __func__, __LINE__, ##__VA_ARGS__); }

#endif
