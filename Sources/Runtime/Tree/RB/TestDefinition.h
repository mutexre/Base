#include <stdio.h>
#include <vector>
#include <iostream>

template <typename Key, typename Value>
char Rt::Tree::RB::Test::All<Key, Value>::nodeColorToChar(typename Rt::Tree::RB::Default<Key, Value>::Node::Color color)
{
    return color == Tree::RB::Default<Key, Value>::Node::Color::Red ? 'r' : 'b';
}

template <typename Key, typename Value>
void Rt::Tree::RB::Test::All<Key, Value>::printTree(Tree::RB::Default<Key, Value>* tree)
{
    tree->traverseInOrder([](typename Rt::Tree::RB::Default<Key, Value>::Node* node) { printf("%u -> %u\n", node->key, node->value); });
    tree->traverseInOrder([](typename Rt::Tree::RB::Default<Key, Value>::Node* node)
                          {
                              for (int i = 0; i < 2; i++)
                                  if (node->children[i])
                                      printf("%u%c; %u%c\n", node->key,
                                                             nodeColorToChar(node->color),
                                                             node->children[i]->key,
                                                             nodeColorToChar(node->children[i]->color));
                                  else
                                      printf("%u%c; nil\n", node->key, nodeColorToChar(node->color));
                          });
}

template <typename Key, typename Value>
void Rt::Tree::RB::Test::All<Key, Value>::printTreeKeys(Tree::RB::Default<Key, Value>* tree)
{
    tree->traverseInOrder([](typename Rt::Tree::RB::Default<Key, Value>::Node* node) { printf("%u ", node->key); });
    printf("\n");
}

template <typename Key, typename Value>
bool Rt::Tree::RB::Test::All<Key, Value>::insertVectorElementsIntoTree(std::vector<Key>* vector,
                                                                       Tree::RB::Default<Key, Value>* tree,
                                                                       bool enableDebugOutput)
{
    for (auto iter = vector->begin(); iter != vector->end(); iter++)
    {
        auto key = *iter;

        if (!tree->insert(key, 0))
        {
            printf("insert %u failed\n", key);
            return false;
        }

        if (enableDebugOutput)
        {
            printf("size: %u\n", tree->getSize());
            printTree(tree);
            printf("\n");
        }
    }
    return true;
}

template <typename Key, typename Value>
void Rt::Tree::RB::Test::All<Key, Value>::printVector(std::vector<Key>* vec)
{
    for (auto iter = vec->begin(); iter != vec->end(); iter++)
        printf("%u ", *iter);
    printf("\n");
}

template <typename Key, typename Value>
std::vector<Key> Rt::Tree::RB::Test::All<Key, Value>::createVector(u4 size, bool shuffle)
{
    std::vector<Key> retval(size);

    Algo::Vector::fillWithIncreasingSequence(retval.begin(), retval.end(), 0, 1);
    std::random_shuffle(retval.begin(), retval.end());

    return retval;
}

template <typename Key, typename Value>
std::vector<Key> Rt::Tree::RB::Test::All<Key, Value>::createRandomVector(u4 size, Key min, Key max)
{
    std::vector<Key> retval(size);
    Algo::Vector::randomizeWithUniqueValues(retval.begin(), retval.end(), min, max);
    return retval;
}

template <typename Key, typename Value>
std::vector<Key> Rt::Tree::RB::Test::All<Key, Value>::createSpecificVector(Key* data, u4 size)
{
    std::vector<Key> retval(size);
    for (auto i = 0; i < size; i++) retval[i] = data[i];
    return retval;
}

template <typename Key, typename Value>
int Rt::Tree::RB::Test::All<Key, Value>::testTree(Tree::RB::Default<Key, Value>* tree,
                                                  std::vector<Key>* input,
                                                  bool enableDebugOutput)
{
    std::vector<Key> sortedInput = *input, output;

    insertVectorElementsIntoTree(input, tree, enableDebugOutput);
    tree->traverseInOrder([&](typename Rt::Tree::RB::Default<Key, Value>::Node* node) { output.push_back(node->key); });
    std::sort(sortedInput.begin(), sortedInput.end());

    s4 found = -1;
    for (auto i = 0; i < output.size(); i++) if (output[i] != sortedInput[i]) { found = i; break; }
    if (found != -1)
    {
        RTTestError("comparision failed at %d (%d != %d)\n", found, (*input)[found], sortedInput[found]);
        return 1;
    }

    return 0;
}

template <typename Key, typename Value>
bool Rt::Tree::RB::Test::All<Key, Value>::findBadTreeAndVector(u4 vectorSize,
                                                               u8 maxNumberOfIterations,
                                                               std::vector<Key>** outputVector,
                                                               Tree::RB::Default<Key, Value>** outputTree)
{
    u8 numberOfIterations = 0;

    while (maxNumberOfIterations <= 0 || numberOfIterations < maxNumberOfIterations)
    {
        Tree::RB::Default<Key, Value>* tree = new Tree::RB::Default<Key, Value>();
        if (tree)
        {
            std::vector<Key>* vector = new std::vector<Key>();
            if (vector)
            {
                *vector = createRandomVector(vectorSize, 0, vectorSize);
                if (testTree(tree, vector, false))
                {
                    *outputVector = vector;
                    *outputTree = tree;
                    return true;
                }
            }

            if (maxNumberOfIterations > 0) numberOfIterations++;
            delete tree;
        }
    }

    return false;
}

template <typename Key, typename Value>
int Rt::Tree::RB::Test::All<Key, Value>::test()
{
//{ 12, 9, 11, 3, 2, 13, 5, 14, 6, 4, 7, 8, 1, 0, 10 };

    Tree::RB::Default<Key, Value> tree;
    std::vector<Key> vector;

    srand((unsigned int)time(0));

#if 0
    vector = createVector(50, true);
    printVector(vector);
    if (testTree(tree, vector)) return 1;
#endif

#if 1
    std::vector<Key>* badVector;
    Tree::RB::Default<Key, Value>* badTree;
    if (findBadTreeAndVector(200, 1000, &badVector, &badTree))
    {
        printTreeKeys(badTree);
        printVector(badVector);

        delete badVector;
        delete badTree;
    }
#endif

#if 0
//    Key data[] = { 12, 9, 11, 3, 2, 13, 5, 14, 6, 4, 7, 8, 1, 0, 10 };
//    Key data[] = { 12, 14, 2, 0, 9, 6, 8, 1, 5, 4, 11, 10, 7, 3, 13 };
    Key data[] = { 6, 8, 7, 1, 0, 4, 5, 2, 3 };
    vector = createSpecificVector(data, sizeof(data) / sizeof(data[0]));
    printVector(&vector);
    if (testTree(&tree, &vector, true)) return 1;
#endif

    return 0;
}
