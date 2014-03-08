#ifndef header_74E20DFB6FB0
#define header_74E20DFB6FB0

namespace Rt
{
    namespace Tree
    {
        namespace RB
        {
            namespace Test
            {
                template <typename Key, typename Value>
                class All : public Rt::Test
                {
                private:
                    static char nodeColorToChar(typename Tree::RB::Default<Key, Value>::Node::Color);

                    static void printTree(Tree::RB::Default<Key, Value>*);
                    static void printTreeKeys(Tree::RB::Default<Key, Value>*);
                    static void printVector(std::vector<Key>*);

                    static bool insertVectorElementsIntoTree(std::vector<Key>*, Tree::RB::Default<Key, Value>*, bool enableDebugOutput);

                    static std::vector<Key> createVector(u4 size, bool shuffle);
                    static std::vector<Key> createRandomVector(u4 size, Key min, Key max);
                    static std::vector<Key> createSpecificVector(Key* data, u4 size);

                    static bool findBadTreeAndVector(u4 vectorSize, u8 maxNumberOfIterations,
                                                     std::vector<Key>** outputVector,
                                                     Tree::RB::Default<Key, Value>** outputTree);

                    static int testTree(Tree::RB::Default<Key, Value>* tree, std::vector<Key>* input, bool enableDebugOutput);

                public:
                    virtual int test();
                };
            }
        }
    }
}

#include <Runtime/Tree/RB/TestDefinition.h>

#endif
