#ifndef header_381D623D8690
#define header_381D623D8690

#include <ostream>
#include <functional>

namespace Rt
{
    namespace Tree
    {
        namespace RB
        {
            template <typename Key, typename Value>
            class Default : public Object
            {
            public:
                class Node
                {
                public:
                    enum class Color
                    {
                        Black,
                        Red
                    };

                public:
                    Color color;
                    Key key;
                    Value value;
                    Node* parent;
                    Node* children[2];
                    u1 directionToParent;

                protected:
                    Node(Key, Value, Color);

                public:
                    Node();
                    Node(Key, Value, Color, Node* parent);
                    Node(Key, Value, Color, Node* parent, Node* leftChild, Node* rightChild, u1 direction);

                    Node* getGrandparent() const;
                    void getGrandparentAndUncle(Node** grandparent, Node** uncle) const;
                    Node* getBrother() const;

                    void attachToAnotherParent(Node* newParent, u1 directionToParent);
                    bool rotate(u1 directionToChild);
                    std::pair<Key, Value> getStdPair() const;
                };

            protected:
                Node* root;
                u4 size;

            protected:
                Node* search(Key) const;

                void insertCase1(Node* node, Node* parentNode);
                void insertCase2(Node* node);
                void insertCase3(Node* node);
                void insertCase4(Node* node, Node* grandparent);
                void insertCase5(Node* node);

                void rotate(Node*, u1 direction);

                bool isConsistent() const;

            public:
                Default();
                virtual ~Default();

                Node* getRoot() const { return root; }
                u4 getSize() const { return size; }
                bool isEmpty() const { return root == 0; }

                virtual void traversePreOrder(Node*, std::function<void (Node*)>);
                virtual void traversePreOrder(std::function<void (Node*)>);

                virtual void traverseInOrder(Node*, std::function<void (Node*)>);
                virtual void traverseInOrder(std::function<void (Node*)>);

                virtual void traverseInReverseOrder(Node*, std::function<void (Node*)>);
                virtual void traverseInReverseOrder(std::function<void (Node*)>);

                virtual void traversePostOrder(Node*, std::function<void (Node*)>);
                virtual void traversePostOrder(std::function<void (Node*)>);

                virtual bool search(Key, Value*) const;
                virtual bool insert(Key, Value);
                virtual bool insert(std::pair<Key, Value>);
                virtual bool erase(Key);
            };
        }
    }
}

#include <Runtime/Tree/RB/NodeDefinition.h>
#include <Runtime/Tree/RB/DefaultDefinition.h>

#endif
