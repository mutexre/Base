#ifndef header_FEDD457959B3
#define header_FEDD457959B3

namespace Rt
{
    class SelfTest : public Test
    {
    public:
        template <typename T>
        struct DistributeBitsTestCase {
            u1 n;
            T bits, pattern, correctValue;

            bool verify(T& computedValue) {
                computedValue = distributeBits(bits, pattern, n);
                return computedValue == correctValue;
            }
        };

        virtual int test() {
            DistributeBitsTestCase<u1> distributeBitsTestCases[] = {
                { 0, 0, 0, 0 },
                { 1, 1, 1, 1 },
                { 1, 0, 1, 0 },
                { 1, 1, 2, 2 },
                { 1, 1, 4, 4 },
                { 1, 1, 8, 8 },
                { 2, 0, 3, 0 },
                { 2, 1, 3, 1 },
                { 2, 2, 3, 2 },
                { 2, 3, 3, 3 },
                { 2, 0, 5, 0 },
                { 2, 1, 5, 1 },
                { 2, 2, 5, 4 },
                { 2, 3, 5, 5 },
                { 3, 5, 26, 18 },
                { 3, 7, 26, 26 }
            };

            for (auto& testCase : distributeBitsTestCases) {
                u1 computedValue;
                bool result = testCase.verify(computedValue);
                printf("distributed \"");
                printBits(testCase.bits, testCase.n);
                printf("\" with pattern ");
                printBits(testCase.pattern, 8 * sizeof(u1));
                printf(" to ");
                printBits(computedValue, 8 * sizeof(u1));
                printf(" %s\n", result ? "Ok" : "Failed");
                if (!result) return 1;
            }

            return 0;
        }
    };
}

#endif
